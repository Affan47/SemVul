imap_make_date_time(time_t t)
{
	static char	s[30];
	struct tm	*tmptr;
	int	tzdiff, tzdiff_hour, tzdiff_min;

	tzdiff = t - mktime(gmtime(&t));
	tzdiff_hour = (int)(tzdiff / 60);
	tzdiff_min = tzdiff_hour % 60;
	tzdiff_hour /= 60;
	tmptr = localtime(&t);
	if (tmptr->tm_isdst > 0)
		tzdiff_hour++;
	snprintf(s, sizeof s, "\"%02d-%s-%04d %02d:%02d:%02d %+03d%02d\"",
			tmptr->tm_mday,
			month_names[tmptr->tm_mon],
			tmptr->tm_year + 1900,
			tmptr->tm_hour,
			tmptr->tm_min,
			tmptr->tm_sec,
			tzdiff_hour,
			tzdiff_min);
	return s;
}
