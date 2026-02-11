time_print(const void *ip, const struct xt_entry_match *match,
                       int numeric)
{
	const struct xt_time_info *info = (const void *)match->data;
	unsigned int h, m, s;

	printf(" TIME");

	if (info->daytime_start != XT_TIME_MIN_DAYTIME ||
	    info->daytime_stop != XT_TIME_MAX_DAYTIME) {
		divide_time(info->daytime_start, &h, &m, &s);
		printf(" from %02u:%02u:%02u", h, m, s);
		divide_time(info->daytime_stop, &h, &m, &s);
		printf(" to %02u:%02u:%02u", h, m, s);
	}
	if (info->weekdays_match != XT_TIME_ALL_WEEKDAYS) {
		printf(" on");
		time_print_weekdays(info->weekdays_match);
	}
	if (info->monthdays_match != XT_TIME_ALL_MONTHDAYS) {
		printf(" on");
		time_print_monthdays(info->monthdays_match, true);
	}
	if (info->date_start != 0) {
		printf(" starting from");
		time_print_date(info->date_start, NULL);
	}
	if (info->date_stop != INT_MAX) {
		printf(" until date");
		time_print_date(info->date_stop, NULL);
	}
	if (!(info->flags & XT_TIME_LOCAL_TZ))
		printf(" UTC");
	if (info->flags & XT_TIME_CONTIGUOUS)
		printf(" contiguous");
}
