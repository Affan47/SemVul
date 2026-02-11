get_exact_cursor(int init) {
	int which = CURS_ARROW;

	if (init) {

		int i;
		for (i=0; i<CURS_MAX; i++) {
			curs_times[i] = 0;
			curs_index[i] = 0;
		}
		last_cursor = 0;
		last_index = 0;
		return -1;
	}

#ifdef MACOSX
	if (macosx_console) {
		return macosx_get_cursor();
	}
#endif

	if (rawfb_vnc_reflect) {
		int last_idx = (int) get_cursor_serial(1);
		if (last_idx) {
			which = last_idx;
		}
		return which;
	}
	if (xfixes_present && dpy) {
#if LIBVNCSERVER_HAVE_LIBXFIXES
		int last_idx = (int) get_cursor_serial(1);
		XFixesCursorImage *xfc;

		if (last_idx) {
			which = last_idx;
		}
		if (! xfixes_first_initialized) {
			return which;
		}

		X_LOCK;
		if (! got_xfixes_cursor_notify && xfixes_base_event_type) {

			XEvent xev;
			if (XCheckTypedEvent(dpy, xfixes_base_event_type +
			    XFixesCursorNotify, &xev)) {
				got_xfixes_cursor_notify++;
			}
		}
		if (! got_xfixes_cursor_notify) {

			X_UNLOCK;
			return which;
		}
		got_xfixes_cursor_notify = 0;


		xfc = XFixesGetCursorImage(dpy);
		X_UNLOCK;
		if (! xfc) {

			return which;
		}

		which = store_cursor(xfc->cursor_serial, xfc->pixels,
		    xfc->width, xfc->height, 32, xfc->xhot, xfc->yhot);

		X_LOCK;
		XFree_wr(xfc);
		X_UNLOCK;
#endif
	}
	return(which);
}
