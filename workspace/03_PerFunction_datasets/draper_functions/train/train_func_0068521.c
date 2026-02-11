pmove(int x, int y) {
	if (x < 0 || y < 0) {
		rfbLog("pmove: skipping negative x or y: %d %d\n", x, y);
		return;
	}
	rfbLog("pmove: x y: %d %d\n", x, y);
	pointer_event(0, x, y, NULL);
	X_LOCK;
	XFlush_wr(dpy);
	X_UNLOCK;
}
