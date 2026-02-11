xcheckmaskevent(Display *d, long mask, XEvent *ev) {
#ifdef MACOSX
	if (macosx_console) {
		if (macosx_checkevent(ev)) {
			return True;
		} else {
			return False;
		}
	}
#endif
	RAWFB_RET(False);

#if NO_X11
	if (!d || !mask) {}
	return False;
#else
	return XCheckMaskEvent(d, mask, ev);
#endif
}
