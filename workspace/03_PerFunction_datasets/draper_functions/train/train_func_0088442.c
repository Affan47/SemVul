ptr_move(int dx, int dy) {
#ifdef UINPUT_OK
	struct input_event ev;
	int d = direct_rel_fd < 0 ? fd : direct_rel_fd;

	if (injectable && strchr(injectable, 'M') == NULL) {
		return;
	}

	memset(&ev, 0, sizeof(ev));

	if (db) fprintf(stderr, "ptr_move(%d, %d) fd=%d\n", dx, dy, d);

	gettimeofday(&ev.time, NULL);
	ev.type = EV_REL;
	ev.code = REL_Y;
	ev.value = dy;
	write(d, &ev, sizeof(ev));

	ev.type = EV_REL;
	ev.code = REL_X;
	ev.value = dx;
	write(d, &ev, sizeof(ev));

	ev.type = EV_SYN;
	ev.code = SYN_REPORT;
	ev.value = 0;
	write(d, &ev, sizeof(ev));
#else
	if (!dx || !dy) {}
#endif
}
