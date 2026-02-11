get_keystate(int *keystate) {
#if NO_X11
	RAWFB_RET_VOID
	if (!keystate) {}
	return;
#else
	int i, k;
	char keys[32];

	RAWFB_RET_VOID


	XQueryKeymap(dpy, keys);
	for (i=0; i<32; i++) {
		char c = keys[i];

		for (k=0; k < 8; k++) {
			if (c & 0x1) {
				keystate[8*i + k] = 1;
			} else {
				keystate[8*i + k] = 0;
			}
			c = c >> 1;
		}
	}
#endif
}
