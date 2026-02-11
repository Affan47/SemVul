pfield_do_fill_line (int start, int stop, bool blank)
{
	xlinecheck(start, stop);
	if (!blank) {
		if (start < visible_left_start) {
			pfield_do_fill_line2 (start, visible_left_start, true);
			start = visible_left_start;
		}
		if (stop > visible_right_stop) {
			pfield_do_fill_line2 (start, visible_right_stop, false);
			blank = true;
			start = visible_right_stop;
		}
	}
	pfield_do_fill_line2 (start, stop, blank);
}
