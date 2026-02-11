list_windows(void) {
	int i, n = 0;
	for (i=0; i < WMAX; i++) {
		char *name;
		Window win = watch[i];
		if (win == None) {
			continue;
		}
		get_wm_name(win, &name);
		fprintf(stdout, "window[%02d] 0x%08lx state: %d slot: %03d \"%s\"\n",
		    ++n, win, state[i], i, name);
		free(name);
	}
	fprintf(stdout, "total windows: %d\n", n);
	ff();
}
