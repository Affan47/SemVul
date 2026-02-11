do_filter(struct abctune *t, char *sel)
{
	int cur_sel, end_sel, n;

	for (;;) {
		if (sscanf(sel, "%d%n", &cur_sel, &n) != 1)
			break;
		sel += n;
		if (*sel == '-') {
			sel++;
			end_sel = (int) ((unsigned) (~0) >> 1);
			if (sscanf(sel, "%d%n", &end_sel, &n) != 1)
				end_sel = (unsigned) ~0 >> 1;
			else
				sel += n;
		} else {
			end_sel = cur_sel;
		}
		do_select(t, cur_sel, end_sel);
		if (*sel != ',')
			break;
		sel++;
	}
}
