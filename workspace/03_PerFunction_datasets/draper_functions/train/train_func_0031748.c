do_months(timelib_ull month, timelib_ull year)
{
	if (timelib_is_leap(year)) {
		return ((month_tab_leap[month - 1] + 1) * SECS_PER_DAY);
	} else {
		return ((month_tab[month - 1]) * SECS_PER_DAY);
	}
}
