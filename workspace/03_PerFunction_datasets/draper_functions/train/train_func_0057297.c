update(struct VSM_data *vd)
{
	int w = COLS / HIST_RANGE;
	int n = w * HIST_RANGE;
	unsigned bm[n], bh[n];
	unsigned max;
	int i, j, scale;

	erase();


	w = COLS / HIST_RANGE;
	n = w * HIST_RANGE;
	for (i = 0; i < n; ++i)
		(void)mvaddch(LINES - 2, i, '-');
	for (i = 0, j = HIST_LOW; i < HIST_RANGE; ++i, ++j) {
		(void)mvaddch(LINES - 2, w * i, '+');
		mvprintw(LINES - 1, w * i, "|1e%d", j);
	}

	mvprintw(0, 0, "%*s", COLS - 1, VSM_Name(vd));


	for (i = 0; i < n; ++i)
		bm[i] = bh[i] = 0;
	for (i = 0, max = 1; i < HIST_BUCKETS; ++i) {
		j = i * n / HIST_BUCKETS;
		bm[j] += bucket_miss[i];
		bh[j] += bucket_hit[i];
		if (bm[j] + bh[j] > max)
			max = bm[j] + bh[j];
	}


	for (i = 0; max / scales[i] > LINES - 3; ++i)
		 ;
	scale = scales[i];

	mvprintw(0, 0, "1:%d, n = %d", scale, nhist);


	for (i = 0; i < n; ++i) {
		for (j = 0; j < bm[i] / scale; ++j)
			(void)mvaddch(LINES - 3 - j, i, '#');
		for (; j < (bm[i] + bh[i]) / scale; ++j)
			(void)mvaddch(LINES - 3 - j, i, '|');
	}

	refresh();
}
