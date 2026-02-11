vw_lookup(Window win) {
	static double last_purge = 0.0;
	double now;
	int i, j, k;

	if (win == None) {
		return NULL;
	}

	now = dnow();
	if (now > last_purge + cache_win) {
		last_purge = now;
		for (i=0; i<VW_CACHE_MAX; i++) {
			vw_cache_win[i] = None;
		}
	}

	j = -1;
	k = -1;
	for (i=0; i<VW_CACHE_MAX; i++) {
		if (vw_cache_win[i] == win) {
			j = i;
			break;
		} else if (vw_cache_win[i] == None) {
			k = i;
			break;
		}
	}

	if (j >= 0) {
MV_hit++;
		return vw_cache_attr+j;

	} else if (k >= 0) {
		XWindowAttributes attr2;
		int rc = valid_window(win, &attr2, 1);
		if (rc) {
			vw_cache_win[k] = win;
			set_attr(&attr2, k);
			return vw_cache_attr+k;
		} else {
			return NULL;
		}
	} else {

		int rc = valid_window(win, &wattr, 1);
		if (rc) {
			return &wattr;
		} else {
			return NULL;
		}
	}
}
