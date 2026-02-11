get_prop(char *str, int len, Atom prop, Window w) {
	int i;
#if !NO_X11
	Atom type;
	int format, slen, dlen;
	unsigned long nitems = 0, bytes_after = 0;
	unsigned char* data = NULL;
#endif

	for (i=0; i<len; i++) {
		str[i] = '\0';
	}
	if (prop == None) {
		return;
	}

	RAWFB_RET_VOID

#if NO_X11
	return;
#else

	slen = 0;
	if (w == None) {
		w = DefaultRootWindow(dpy);
	}

	do {
		if (XGetWindowProperty(dpy, w,
		    prop, nitems/4, len/16, False,
		    AnyPropertyType, &type, &format, &nitems, &bytes_after,
		    &data) == Success) {

			dlen = nitems * (format/8);
			if (slen + dlen > len) {

				XFree_wr(data);
				break;
			}
			memcpy(str+slen, data, dlen);
			slen += dlen;
			str[slen] = '\0';
			XFree_wr(data);
		}
	} while (bytes_after > 0);
#endif
}
