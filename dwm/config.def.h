/* See LICENSE file for copyright and license details. */

/* appearance */
static const unsigned int borderpx  = 3;        /* border pixel of windows */
static const unsigned int snap      = 32;       /* snap pixel */
static const int showbar            = 1;        /* 0 means no bar */
static const int topbar             = 1;        /* 0 means bottom bar */
/*  Display modes of the tab bar: never shown, always shown, shown only in  */
/*  monocle mode in the presence of several windows.                        */
/*  Modes after showtab_nmodes are disabled.                                */
enum showtab_modes { showtab_never, showtab_auto, showtab_nmodes, showtab_always};
static const int showtab			= showtab_auto;        /* Default tab bar show mode */
static const int toptab				= True;               /* False means bottom tab bar */
static const char *fonts[]          = { "Spleen:style=Regular:pixelsize=18" };
static const char dmenufont[]       = "Spleen:style=Regular:pixelsize=18";
//static const char col_gray1[]       = "#2e3440";
static const char col_gray1[]       = "#70A9A1";
static const char col_gray2[]       = "#444444";
static const char col_gray3[]       = "#d8dee9";
static const char col_gray4[]       = "#CFE0C3";
static const char col_cyan[]        = "#A833B9";
static const char *colors[][3]      = {
	/*               fg         bg         border   */
	[SchemeNorm] = { col_gray3, col_gray2, col_gray1 },
	[SchemeSel]  = { col_gray4, col_gray1,  col_gray4  },
	[SchemeStatus]  = { col_gray3, col_cyan,  "#000000"  }, // Statusbar right {text,background,not used but cannot be empty}
	[SchemeTagsSel]  = { col_gray2, col_gray1,  "#000000"  }, // Tagbar left selected {text,background,not used but cannot be empty}
  [SchemeTagsNorm]  = { col_gray4, col_gray1,  "#000000"  }, // Tagbar left unselected {text,background,not used but cannot be empty}
  [SchemeInfoSel]  = { col_gray2, col_gray4,  "#000000"  }, // infobar middle  selected {text,background,not used but cannot be empty}
  [SchemeInfoNorm]  = { col_gray3, col_gray4,  "#000000"  }, // infobar middle  unselected {text,background,not used but cannot be empty}
 };


/* tagging */
static const char *tags[] = { "Ͼli", "Ғirefox", "ϻusic", "ϻovie", "5", "6", "7", "8", "9" };

static const Rule rules[] = {
	/* xprop(1):
	 *	WM_CLASS(STRING) = instance, class
	 *	WM_NAME(STRING) = title
	 */
	/* class      instance      title       tags mask     isfloating   monitor */
	{ "Firefox",  NULL,         NULL,       1 << 1,       0,           -1 },
	{ "st",       "music",      NULL,       1 << 2,       0,           -1 },
	{ "st",       "st",         NULL,       1 << 0,       0,           -1 },
	{ "st",       "temporary",  "float",    0,            1,           -1 },
	{ "mpv",       "gl",        NULL,       1 << 3,       1,           -1 },
};

/* layout(s) */
static const float mfact     = 0.55; /* factor of master area size [0.05..0.95] */
static const int nmaster     = 1;    /* number of clients in master area */
static const int resizehints = 1;    /* 1 means respect size hints in tiled resizals */

static const Layout layouts[] = {
	/* symbol     arrange function */
	{ "[]=",      tile },    /* first entry is default */
	{ "><>",      NULL },    /* no layout function means floating behavior */
	{ "[M]",      monocle },
};

/* key definitions */
#define MODKEY Mod4Mask
#define ALTKEY Mod1Mask
#define TAGKEYS(KEY,TAG) \
	{ MODKEY,                       KEY,      view,           {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask,           KEY,      toggleview,     {.ui = 1 << TAG} }, \
	{ MODKEY|ShiftMask,             KEY,      tag,            {.ui = 1 << TAG} }, \
	{ MODKEY|ControlMask|ShiftMask, KEY,      toggletag,      {.ui = 1 << TAG} },

/* helper for spawning shell commands in the pre dwm-5.0 fashion */
#define SHCMD(cmd) { .v = (const char*[]){ "/bin/sh", "-c", cmd, NULL } }

/* commands */
static char dmenumon[2] = "0"; /* component of dmenucmd, manipulated in spawn() */
static const char *dmenucmd[] = { "dmenu_run", "-m", dmenumon, "-fn", dmenufont, "-nb", col_gray1, "-nf", col_gray2, "-sb", col_gray1, "-sf", col_gray2, "-c", "-g", "3", "-l", "5", NULL };
static const char *termcmd[]  = { "st", NULL };

static Key keys[] = {
	/* modifier                     key        function        argument */
	{ MODKEY,                       XK_p,      spawn,          {.v = dmenucmd } },
	{ MODKEY, 	                XK_Return, spawn,          {.v = termcmd } },
	{ MODKEY,                       XK_b,      togglebar,      {0} },
	{ MODKEY,                       XK_w,      tabmode,        {-1} },
	{ MODKEY,                       XK_j,      focusstack,     {.i = +1 } },
	{ MODKEY,                       XK_k,      focusstack,     {.i = -1 } },
	{ MODKEY,                       XK_i,      incnmaster,     {.i = +1 } },
	{ MODKEY,                       XK_d,      incnmaster,     {.i = -1 } },
	{ MODKEY,                       XK_h,      setmfact,       {.f = -0.05} },
	{ MODKEY,                       XK_l,      setmfact,       {.f = +0.05} },
	{ MODKEY,                       XK_g, 	   zoom,           {0} },
	{ MODKEY,                       XK_Tab,    view,           {0} },
	{ MODKEY|ShiftMask,             XK_c,      killclient,     {0} },
	{ MODKEY,                       XK_t,      setlayout,      {.v = &layouts[0]} },
	{ MODKEY,                       XK_f,      setlayout,      {.v = &layouts[1]} },
	{ MODKEY,                       XK_m,      setlayout,      {.v = &layouts[2]} },
	{ MODKEY,                       XK_space,  setlayout,      {0} },
	{ MODKEY|ShiftMask,             XK_space,  togglefloating, {0} },
	{ MODKEY,                       XK_0,      view,           {.ui = ~0 } },
	{ MODKEY|ShiftMask,             XK_0,      tag,            {.ui = ~0 } },
	{ MODKEY,                       XK_comma,  focusmon,       {.i = -1 } },
	{ MODKEY,                       XK_period, focusmon,       {.i = +1 } },
	{ MODKEY|ShiftMask,             XK_comma,  tagmon,         {.i = -1 } },
	{ MODKEY|ShiftMask,             XK_period, tagmon,         {.i = +1 } },
	TAGKEYS(                        XK_1,                      0)
	TAGKEYS(                        XK_2,                      1)
	TAGKEYS(                        XK_3,                      2)
	TAGKEYS(                        XK_4,                      3)
	TAGKEYS(                        XK_5,                      4)
	TAGKEYS(                        XK_6,                      5)
	TAGKEYS(                        XK_7,                      6)
	TAGKEYS(                        XK_8,                      7)
	TAGKEYS(                        XK_9,                      8)
	{MODKEY|ShiftMask,             XK_q,      quit,           {1} },
	{MODKEY|ControlMask|ShiftMask, XK_q,      quit,           {0} }, 
/*------------------------CustomeKey--------------------------*/
	{0,XF86XK_AudioMute,	 	spawn, SHCMD("pamixer -t ; kill -44 $(pidof dwmblocks) ")},
	{0,XF86XK_AudioRaiseVolume,	spawn, SHCMD("pamixer -i 5 ; kill -44 $(pidof dwmblocks) ")},
	{0,XF86XK_AudioLowerVolume,	spawn, SHCMD("pamixer -d 5 ; kill -44 $(pidof dwmblocks) ")},
	{0,XF86XK_MonBrightnessUp,	spawn, SHCMD("light -A 5 ; kill -44 $(pidof dwmblocks) ")},
	{0,XF86XK_MonBrightnessDown,	spawn, SHCMD("light -U 5 ; kill -44 $(pidof dwmblocks) ")},
	{0,XF86XK_Launch1,	spawn, SHCMD("$HOME/.local/bin/tptoggle.sh")},
	{MODKEY|ALTKEY,	 		XK_n, spawn , SHCMD("st -n music -c st -t ncmpcpp -e ncmpcpp")}, 
	{MODKEY|ALTKEY,	 		XK_s, spawn , SHCMD("sxiv -t ~/.local/dot/wals")}, 
	{MODKEY|ALTKEY,	       	 XK_m, spawn , SHCMD("st -n lf -c st -t movies -e lf ~/.local/movies")}, 
	{MODKEY|ShiftMask,     	        XK_Return, spawn, SHCMD("st -n temporary -c st -t float")          },
	{MODKEY|ALTKEY,     	        XK_f, spawn, SHCMD("st -n temporary -c st -t lf -e lf")          },
	{MODKEY|ALTKEY,     	        XK_r, spawn, SHCMD("redshift -c ~/.config/redshift/redshift.conf")          },

};

/* button definitions */
/* click can be ClkTagBar, ClkLtSymbol, ClkStatusText, ClkWinTitle, ClkClientWin, or ClkRootWin */
static Button buttons[] = {
	/* click                event mask      button          function        argument */
	{ ClkLtSymbol,          0,              Button1,        setlayout,      {0} },
	{ ClkLtSymbol,          0,              Button3,        setlayout,      {.v = &layouts[2]} },
	{ ClkWinTitle,          0,              Button2,        zoom,           {0} },
	{ ClkStatusText,        0,              Button2,        spawn,          {.v = termcmd } },
	{ ClkClientWin,         MODKEY,         Button1,        movemouse,      {0} },
	{ ClkClientWin,         MODKEY,         Button2,        togglefloating, {0} },
	{ ClkClientWin,         MODKEY,         Button3,        resizemouse,    {0} },
	{ ClkTagBar,            0,              Button1,        view,           {0} },
	{ ClkTagBar,            0,              Button3,        toggleview,     {0} },
	{ ClkTagBar,            MODKEY,         Button1,        tag,            {0} },
	{ ClkTagBar,            MODKEY,         Button3,        toggletag,      {0} },
	{ ClkTabBar,            0,              Button1,        focuswin,       {0} },
};

