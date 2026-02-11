e_calendar_item_preserve_day_selection (ECalendarItem *calitem,
                                        gint selected_day,
                                        gint *month_offset,
                                        gint *day)
{
	gint year, month, weekday, days, days_in_month;
	struct tm tmp_tm = { 0 };

	year = calitem->year;
	month = calitem->month + *month_offset;
	e_calendar_item_normalize_date (calitem, &year, &month);

	tmp_tm.tm_year = year - 1900;
	tmp_tm.tm_mon = month;
	tmp_tm.tm_mday = *day;
	tmp_tm.tm_isdst = -1;
	mktime (&tmp_tm);


	weekday = (tmp_tm.tm_wday + 6) % 7;


	days = (weekday + 7 - selected_day) % 7;

	*day -= days;
	if (*day <= 0) {
		month--;
		if (month == -1) {
			year--;
			month = 11;
		}
		days_in_month = DAYS_IN_MONTH (year, month);
		(*month_offset)--;
		*day += days_in_month;
	}
}
