_g_time_val_from_exif_date (const char *exif_date,
			    GTimeVal   *time_)
{
	struct tm tm;
	long   val;

	g_return_val_if_fail (time_ != NULL, FALSE);

	if (exif_date == NULL)
		return FALSE;

	while (g_ascii_isspace (*exif_date))
		exif_date++;

	if (*exif_date == '\0')
		return FALSE;

	if (! g_ascii_isdigit (*exif_date))
		return FALSE;


	val = g_ascii_strtoull (exif_date, (char **)&exif_date, 10);
	tm.tm_year = val - 1900;

	if (*exif_date != ':')
		return FALSE;


	exif_date++;
	tm.tm_mon = g_ascii_strtoull (exif_date, (char **)&exif_date, 10) - 1;

	if (*exif_date != ':')
		return FALSE;


	exif_date++;
	tm.tm_mday = g_ascii_strtoull (exif_date, (char **)&exif_date, 10);

  	if (*exif_date != ' ')
		return FALSE;


  	val = g_ascii_strtoull (exif_date, (char **)&exif_date, 10);
  	tm.tm_hour = val;

  	if (*exif_date != ':')
		return FALSE;


	exif_date++;
	tm.tm_min = g_ascii_strtoull (exif_date, (char **)&exif_date, 10);

	if (*exif_date != ':')
		return FALSE;


	exif_date++;
	tm.tm_sec = strtoul (exif_date, (char **)&exif_date, 10);

	time_->tv_sec = mktime (&tm);
	time_->tv_usec = 0;


	if ((*exif_date == ',') || (*exif_date == '.')) {
		glong mul = 100000;

		while (g_ascii_isdigit (*++exif_date)) {
			time_->tv_usec += (*exif_date - '0') * mul;
			mul /= 10;
		}
	}

	while (g_ascii_isspace (*exif_date))
		exif_date++;

	return *exif_date == '\0';
}
