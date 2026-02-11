delete_win(Window win) {
	int i;
	for (i=0; i < WMAX; i++) {
		if (watch[i] == win) {
			watch[i] = None;
			state[i] = 0;
			if (appshare_debug) {fprintf(stderr, "deleting: 0x%lx at %d\n", win, i); ff();}
		}
	}
}
