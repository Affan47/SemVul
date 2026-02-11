procheader_date_parse_to_tm(const gchar *src, struct tm *t, char *zone)
{
	gchar weekday[11];
	gint day;
	gchar month[10];
	gint year;
	gint hh, mm, ss;
	GDateMonth dmonth;
	gchar *p;

	if (!t)
		return FALSE;

	memset(t, 0, sizeof *t);

	if (procheader_scan_date_string(src, weekday, &day, month, &year,
					&hh, &mm, &ss, zone) < 0) {
		g_warning("Invalid date: %s\n", src);
		return FALSE;
	}


	if (year < 100) {
		if (year < 70)
			year += 2000;
		else
			year += 1900;
	}

	month[3] = '\0';
	if ((p = strstr(monthstr, month)) != NULL)
		dmonth = (gint)(p - monthstr) / 3 + 1;
	else {
		g_warning("Invalid month: %s\n", month);
		dmonth = G_DATE_BAD_MONTH;
	}

	t->tm_sec = ss;
	t->tm_min = mm;
	t->tm_hour = hh;
	t->tm_mday = day;
	t->tm_mon = dmonth - 1;
	t->tm_year = year - 1900;
	t->tm_wday = 0;
	t->tm_yday = 0;
	t->tm_isdst = -1;

	mktime(t);

	return TRUE;
}
