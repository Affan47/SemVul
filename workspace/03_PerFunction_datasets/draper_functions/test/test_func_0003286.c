get_wm_frame_pos(int *px, int *py, int *x, int *y, int *w, int *h,
    Window *frame, Window *win) {
#if !NO_X11
	Window r, c;
	XWindowAttributes attr;
	Bool ret;
	int rootx, rooty, wx, wy;
	unsigned int mask;
#endif

#ifdef MACOSX
	if (macosx_console) {
		return macosx_get_wm_frame_pos(px, py, x, y, w, h, frame, win);
	}
#endif

	RAWFB_RET(0)

#if NO_X11
	if (!px || !py || !x || !y || !w || !h || !frame || !win) {}
	return 0;
#else


	ret = XQueryPointer_wr(dpy, rootwin, &r, &c, &rootx, &rooty, &wx, &wy,
	    &mask);

	*frame = c;


	*px = rootx;
	*py = rooty;

	if (!ret || ! c || c == rootwin) {

		return 0;
	}


	if (! valid_window(c, &attr, 1)) {
		return 0;
	}

	*x = attr.x;
	*y = attr.y;
	*w = attr.width;
	*h = attr.height;

#if 0

	if (attr.border_width > 0) {
		*w += 2 * attr.border_width;
		*h += 2 * attr.border_width;
	}
#endif

	if (win != NULL) {
		*win = descend_pointer(5, c, NULL, 0);
	}

	return 1;
#endif
}
