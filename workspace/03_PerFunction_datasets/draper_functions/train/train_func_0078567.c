DoRegisterName(dpy, name)
    Display	*dpy;
    char_u	*name;
{
    Window	w;
    XErrorHandler old_handler;
#define MAX_NAME_LENGTH 100
    char_u	propInfo[MAX_NAME_LENGTH + 20];

    if (commProperty == None)
    {
	if (SendInit(dpy) < 0)
	    return -2;
    }


    XGrabServer(dpy);
    w = LookupName(dpy, name, FALSE, NULL);
    if (w != (Window)0)
    {
	Status		status;
	int		dummyInt;
	unsigned int	dummyUns;
	Window		dummyWin;


	old_handler = XSetErrorHandler(x_error_check);
	status = XGetGeometry(dpy, w, &dummyWin, &dummyInt, &dummyInt,
				  &dummyUns, &dummyUns, &dummyUns, &dummyUns);
	(void)XSetErrorHandler(old_handler);
	if (status != Success && w != commWindow)
	{
	    XUngrabServer(dpy);
	    XFlush(dpy);
	    return -1;
	}
	(void)LookupName(dpy, name, TRUE, NULL);
    }
    sprintf((char *)propInfo, "%x %.*s", (int_u)commWindow,
						       MAX_NAME_LENGTH, name);
    old_handler = XSetErrorHandler(x_error_check);
    got_x_error = FALSE;
    XChangeProperty(dpy, RootWindow(dpy, 0), registryProperty, XA_STRING, 8,
		    PropModeAppend, propInfo, STRLEN(propInfo) + 1);
    XUngrabServer(dpy);
    XSync(dpy, False);
    (void)XSetErrorHandler(old_handler);

    if (!got_x_error)
    {
#ifdef FEAT_EVAL
	set_vim_var_string(VV_SEND_SERVER, name, -1);
#endif
	serverName = vim_strsave(name);
#ifdef FEAT_TITLE
	need_maketitle = TRUE;
#endif
	return 0;
    }
    return -2;
}
