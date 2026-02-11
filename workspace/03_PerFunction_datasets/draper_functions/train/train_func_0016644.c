filter_accept_holes(const char *accept_field, const char *time_field, struct timer **tptr)
{
	struct timer *t2;
	int val;

	val = convert_date(accept_field);
	if (unlikely(val < 0)) {
		truncated_line(linenum, line);
		return;
	}

	t2 = insert_value(&timers[0], tptr, val);
	t2->count++;
	return;
}
