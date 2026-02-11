valid_window(Window win, XWindowAttributes *attr_ret, int bequiet) {
	XWindowAttributes attr, *pattr;
#if !NO_X11
	XErrorHandler old_handler;
	int ok = 0;
#endif

	if (attr_ret == NULL) {
		pattr = &attr;
	} else {
		pattr = attr_ret;
	}

	if (win == None) {
		return 0;
	}

#ifdef MACOSX
	if (macosx_console) {
		return macosx_valid_window(win, attr_ret);
	}
#endif

	RAWFB_RET(0)

#if NO_X11
	nox11_exit(1);
	if (!win || !attr_ret || !bequiet) {}
	return 0;
#else

	old_handler = XSetErrorHandler(trap_xerror);
	trapped_xerror = 0;
	if (XGetWindowAttributes(dpy, win, pattr)) {
		ok = 1;
	}
	if (trapped_xerror && trapped_xerror_event) {
		if (! quiet && ! bequiet) {
			rfbLog("valid_window: trapped XError: %s (0x%lx)\n",
			    xerror_string(trapped_xerror_event), win);
		}
		ok = 0;
	}
	XSetErrorHandler(old_handler);
	trapped_xerror = 0;

	return ok;
#endif
}
