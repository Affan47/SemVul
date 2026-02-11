fmt_asterisk(bool colon, bool atsign)
{
	int n=0;

	fmt_max_param(1);
	fmt_not_colon_atsign(colon, atsign);
	if (atsign) {
		fmt_set_param(0, &n, fmt_int, 0);
		if (n < 0 || n >= fmt_end)
			fmt_error("can't goto");
		fmt_index = n;
	} else if (colon) {
		fmt_set_param(0, &n, fmt_int, 1);
		if (n > fmt_index)
			fmt_error("can't back up");
		fmt_index -= n;
	} else {
		fmt_set_param(0, &n, fmt_int, 1);
		while (n-- > 0)
			fmt_advance();
	}
}
