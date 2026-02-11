e_calendar_item_round_up_selection (ECalendarItem *calitem,
                                    gint *month_offset,
                                    gint *day)
{
	GDateWeekday weekday;
	gint year, month, days, days_in_month;
	struct tm tmp_tm = { 0 };

	year = calitem->year;
	month = calitem->month + *month_offset;
	e_calendar_item_normalize_date (calitem, &year, &month);

	tmp_tm.tm_year = year - 1900;
	tmp_tm.tm_mon = month;
	tmp_tm.tm_mday = *day;
	tmp_tm.tm_isdst = -1;
	mktime (&tmp_tm);


	weekday = e_weekday_from_tm_wday (tmp_tm.tm_wday);
	days = e_weekday_get_days_between (weekday, calitem->week_start_day);

	*day += days;
	days_in_month = DAYS_IN_MONTH (year, month);
	if (*day > days_in_month) {
		(*month_offset)++;
		*day -= days_in_month;
	}
}
