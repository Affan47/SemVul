handle_year (char const *text, GORegmatch const *pm)
{
	int y;

	if (pm->rm_so == pm->rm_eo)
		return current_year ();

	y = handle_int (text, pm, 0, 9999, 4);

	if (y < 0)
		return -1;
	else if (y <= 29)
		return 2000 + y;
	else if (y <= 99)
		return 1900 + y;
	else if (y < (gnm_datetime_allow_negative () ? 1582 : 1900))
		return -1;
	else
		return y;
}
