make_cursor_pixmap(
    XDisplay* dpy, XWindow root, const int* scanline
) {
    Pixmap dst = XCreatePixmap(dpy, root, cursorWidth, cursorHeight, 1);
    GC g = XCreateGC(dpy, dst, 0, nil);
    XSetForeground(dpy, g, 0);
    XSetFillStyle(dpy, g, FillSolid);
    XFillRectangle(dpy, dst, g, 0, 0, cursorWidth, cursorHeight);
    XSetForeground(dpy, g, 1);

    register int i, j;
    register unsigned s1, s2;
    for (i = 0; i < cursorHeight; i++) {
	s1 = scanline[i];
	s2 = 1;
	for (j = 0; j < cursorWidth; j++) {
	    if ((s1 & s2) != 0) {
		XDrawPoint(dpy, dst, g, cursorWidth - 1 - j, i);
	    }
	    s2 <<= 1;
	}
    }
    XFreeGC(dpy, g);
    return dst;
}
