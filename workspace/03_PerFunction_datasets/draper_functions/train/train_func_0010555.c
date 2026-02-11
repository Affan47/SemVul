check_x11_pointer(void) {
	Window root_w, child_w;
	rfbBool ret = 0;
	int root_x, root_y, win_x, win_y;
	int x, y, rint;
	unsigned int mask;

	if (unixpw_in_progress) return 0;

#ifdef MACOSX
	if (macosx_console) {
		ret = macosx_get_cursor_pos(&root_x, &root_y);
	} else {
		RAWFB_RET(0)
	}
#else

	RAWFB_RET(0)

#   if NO_X11
	return 0;
#   endif

#endif


#if ! NO_X11
	if (dpy) {
		X_LOCK;
		ret = XQueryPointer_wr(dpy, rootwin, &root_w, &child_w, &root_x, &root_y,
		    &win_x, &win_y, &mask);
		X_UNLOCK;
	}
#else
	if (!mask || !win_y || !win_x || !child_w || !root_w) {}
#endif

if (0) fprintf(stderr, "check_x11_pointer %d %d\n", root_x, root_y);
	if (! ret) {
		return 0;
	}
	if (debug_pointer) {
		static int last_x = -1, last_y = -1;
		if (root_x != last_x || root_y != last_y) {
			rfbLog("XQueryPointer:     x:%4d, y:%4d\n",
			    root_x, root_y);
			if (debug_pointer > 1) {
				rfbLog("check_x11_pointer x:%4d y:%4d "
				    "d: %dx%d+%d+%d wd: %dx%d cd: %dx%d+%d+%d\n",
				    root_x - off_x - coff_x, root_y - off_y - coff_y, dpy_x, dpy_y, off_x, off_y, wdpy_x, wdpy_y, cdpy_x, cdpy_y, coff_x, coff_y);
			}
		}
		last_x = root_x;
		last_y = root_y;
	}


	x = root_x - off_x - coff_x;
	y = root_y - off_y - coff_y;

	if (clipshift) {
		static int cnt = 0;
		if (x < 0 || y < 0 || x >= dpy_x || y >= dpy_y)  {
			if (cnt++ % 4 != 0) {
				if (debug_pointer) {
					rfbLog("Skipping cursor_position() x:%4d y:%4d outside our "
					    "clipshift dpy_x/y: %d/%d wdpy_x/y: %d/%d cdpy_x/y: %d/%d\n",
					    x, y, dpy_x, dpy_y, wdpy_x, wdpy_y, cdpy_x, cdpy_y);
				}
			}
			return 0;
		}
	}


	cursor_position(x, y);


	rint = set_cursor(x, y, get_which_cursor());
	return rint;
}
