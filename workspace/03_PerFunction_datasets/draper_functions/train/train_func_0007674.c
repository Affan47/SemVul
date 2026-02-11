xrecord_emacs_scroll_keysym(rfbKeySym keysym) {
	KeySym sym = (KeySym) keysym;
	if (sym == XK_N || sym == XK_n || sym == XK_P || sym == XK_p) {
		return 1;
	}

	return 0;
}
