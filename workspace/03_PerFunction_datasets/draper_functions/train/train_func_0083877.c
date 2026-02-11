refresh_screen(int push) {
	int i;
	if (!screen) {
		return;
	}
	mark_rect_as_modified(0, 0, dpy_x, dpy_y, 0);
	for (i=0; i<push; i++) {
		rfbPE(-1);
	}
}
