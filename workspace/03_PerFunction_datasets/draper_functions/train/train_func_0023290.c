gda_timestamp_change_timezone (GdaTimestamp *ts, glong ntz)
{
	g_return_if_fail (ts);
	g_return_if_fail (gda_timestamp_valid (ts));
	g_return_if_fail ((ntz > - 12 * 3600) && (ntz < 12 * 3600));

	if (ts->timezone == ntz)
		return;

	if (ts->timezone != GDA_TIMEZONE_INVALID) {
		glong nsec;
		nsec = ts->hour * 3600 + ts->minute * 60 + ts->second - ts->timezone + ntz;
		if (nsec < 0) {
			GDate *date;
			date = g_date_new_dmy ((GDateDay) ts->day, (GDateMonth) ts->month, (GDateYear) ts->year);
			g_date_subtract_days (date, 1);
			ts->year = g_date_get_year (date);
			ts->month = g_date_get_month (date);
			ts->day = g_date_get_day (date);
			g_date_free (date);
			nsec += 86400;
		}
		else if (nsec >= 86400) {
			GDate *date;
			date = g_date_new_dmy ((GDateDay) ts->day, (GDateMonth) ts->month, (GDateYear) ts->year);
			g_date_add_days (date, 1);
			ts->year = g_date_get_year (date);
			ts->month = g_date_get_month (date);
			ts->day = g_date_get_day (date);
			g_date_free (date);
			nsec -= 86400;
		}


		gint n;
		n = nsec / 3600;
		ts->hour = (gushort) n;


		nsec -= n * 3600;
		n = nsec / 60;
		ts->minute = (gushort) n;


		nsec -= n * 60;
		ts->second = (gushort) nsec;
	}

	ts->timezone = ntz;
}
