cmap_xi(XImage *xi, Window win, int win_depth) {
#if NO_X11
	if (!xi || !win || !win_depth) {}
	return NULL;
#else
	XWindowAttributes attr;
	char *d;

	if (xi) {
		XDestroyImage(xi);
	}
	if (! dpy || ! valid_window(win, &attr, 1)) {
		return (XImage *) NULL;
	}
	if (win_depth == 24) {
		d = (char *) malloc(dpy_x * dpy_y * 4);
	} else if (win_depth <= 16) {
		if (win_depth > 8) {
			d = (char *) malloc(dpy_x * dpy_y * 2);
		} else {
			d = (char *) malloc(dpy_x * dpy_y * 1);
		}
	} else {
		return (XImage *) NULL;
	}
	return XCreateImage(dpy, attr.visual, win_depth, ZPixmap, 0, d, dpy_x, dpy_y, 8, 0);
#endif
}
