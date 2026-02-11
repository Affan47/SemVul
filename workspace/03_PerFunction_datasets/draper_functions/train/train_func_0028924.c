get_wm_name(Window win, char **name) {
	int ok;

#if !NO_X11
        XErrorHandler old_handler = XSetErrorHandler(trap_xerror);
	ok = XFetchName(dpy, win, name);
       	XSetErrorHandler(old_handler);
#endif

	if (!ok || *name == NULL) {
		*name = strdup("unknown");
	}
}
