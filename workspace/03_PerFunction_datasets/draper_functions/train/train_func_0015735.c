setup_term_clip()
{
    int		z = 0;
    char	*strp = "";
    Widget	AppShell;

    if (!x_connect_to_server())
	return;

    open_app_context();
    if (app_context != NULL && xterm_Shell == (Widget)0)
    {
	int (*oldhandler)();
#if defined(HAVE_SETJMP_H)
	int (*oldIOhandler)();
#endif
# if defined(HAVE_GETTIMEOFDAY) && defined(HAVE_SYS_TIME_H)
	struct timeval  start_tv;

	if (p_verbose > 0)
	    gettimeofday(&start_tv, NULL);
# endif


	oldhandler = XSetErrorHandler(x_error_check);

#if defined(HAVE_SETJMP_H)

	oldIOhandler = XSetIOErrorHandler(x_IOerror_check);
	mch_startjmp();
	if (SETJMP(lc_jump_env) != 0)
	{
	    mch_didjmp();
	    xterm_dpy = NULL;
	}
	else
#endif
	{
	    xterm_dpy = XtOpenDisplay(app_context, xterm_display,
		    "vim_xterm", "Vim_xterm", NULL, 0, &z, &strp);
#if defined(HAVE_SETJMP_H)
	    mch_endjmp();
#endif
	}

#if defined(HAVE_SETJMP_H)

	(void)XSetIOErrorHandler(oldIOhandler);
#endif

	(void)XSetErrorHandler(oldhandler);

	if (xterm_dpy == NULL)
	{
	    if (p_verbose > 0)
		verb_msg((char_u *)_("Opening the X display failed"));
	    return;
	}


	(void)XSetIOErrorHandler(x_IOerror_handler);

# if defined(HAVE_GETTIMEOFDAY) && defined(HAVE_SYS_TIME_H)
	if (p_verbose > 0)
	{
	    verbose_enter();
	    xopen_message(&start_tv);
	    verbose_leave();
	}
# endif


	AppShell = XtVaAppCreateShell("vim_xterm", "Vim_xterm",
		applicationShellWidgetClass, xterm_dpy,
		NULL);
	if (AppShell == (Widget)0)
	    return;
	xterm_Shell = XtVaCreatePopupShell("VIM",
		topLevelShellWidgetClass, AppShell,
		XtNmappedWhenManaged, 0,
		XtNwidth, 1,
		XtNheight, 1,
		NULL);
	if (xterm_Shell == (Widget)0)
	    return;

	x11_setup_atoms(xterm_dpy);
	x11_setup_selection(xterm_Shell);
	if (x11_display == NULL)
	    x11_display = xterm_dpy;

	XtRealizeWidget(xterm_Shell);
	XSync(xterm_dpy, False);
	xterm_update();
    }
    if (xterm_Shell != (Widget)0)
    {
	clip_init(TRUE);
	if (x11_window == 0 && (strp = getenv("WINDOWID")) != NULL)
	    x11_window = (Window)atol(strp);

	if (test_x11_window(xterm_dpy) == FAIL)
	    x11_window = 0;
	if (x11_window != 0)
	    xterm_trace = 0;
    }
}
