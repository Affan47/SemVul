create_xdamage_if_needed(int force) {

	RAWFB_RET_VOID

	if (force) {}

#if LIBVNCSERVER_HAVE_LIBXDAMAGE
	if (! xdamage || force) {
		X_LOCK;
		xdamage = XDamageCreate(dpy, window, XDamageReportRawRectangles);
		XDamageSubtract(dpy, xdamage, None, None);
		X_UNLOCK;
		rfbLog("created   xdamage object: 0x%lx\n", xdamage);
	}
#endif
}
