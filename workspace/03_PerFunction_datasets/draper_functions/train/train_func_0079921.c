update(const struct VSM_data *vd, int period)
{
	struct top *tp, *tp2;
	int l, len;
	double t = 0;
	static time_t last = 0;
	static unsigned n;
	time_t now;

	now = time(NULL);
	if (now == last)
		return;
	last = now;

	l = 1;
	if (n < period)
		n++;
	AC(erase());
	AC(mvprintw(0, 0, "%*s", COLS - 1, VSM_Name(vd)));
	AC(mvprintw(0, 0, "list length %u", ntop));
	VTAILQ_FOREACH_SAFE(tp, &top_head, list, tp2) {
		if (++l < LINES) {
			len = tp->clen;
			if (len > COLS - 20)
				len = COLS - 20;
			AC(mvprintw(l, 0, "%9.2f %-*.*s %*.*s\n",
			    tp->count, maxfieldlen, maxfieldlen,
			    VSL_tags[tp->tag],
			    len, len, tp->rec_data));
			t = tp->count;
		}
		tp->count += (1.0/3.0 - tp->count) / (double)n;
		if (tp->count * 10 < t || l > LINES * 10) {
			VTAILQ_REMOVE(&top_head, tp, list);
			free(tp->rec_data);
			free(tp);
			ntop--;
		}
	}
	AC(refresh());
}
