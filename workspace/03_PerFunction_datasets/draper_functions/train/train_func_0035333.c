mktime_from_string (char *month,
		    char *mday,
		    char *year)
{
	static char  *months[] = { "Jan", "Feb", "Mar", "Apr", "May", "Jun",
				   "Jul", "Aug", "Sep", "Oct", "Nov", "Dec" };
	struct tm     tm = {0, };

	tm.tm_isdst = -1;

	if (month != NULL) {
		int i;
		for (i = 0; i < 12; i++)
			if (strcmp (months[i], month) == 0) {
				tm.tm_mon = i;
				break;
			}
	} else
		tm.tm_mon = 0;

	if (mday != NULL)
		tm.tm_mday = atoi (mday);
	else
		tm.tm_mday = 1;

	if (year != NULL) {
		if (strchr (year, ':') != NULL) {
			char **fields = g_strsplit (year, ":", 2);
			if (g_strv_length (fields) == 2) {
				time_t      now;
				struct tm  *now_tm;

				tm.tm_hour = atoi (fields[0]);
				tm.tm_min = atoi (fields[1]);

				now = time(NULL);
				now_tm = localtime (&now);
				tm.tm_year = now_tm->tm_year;
			}
		} else
			tm.tm_year = atoi (year) - 1900;
	} else
		tm.tm_year = 70;

	return mktime (&tm);
}
