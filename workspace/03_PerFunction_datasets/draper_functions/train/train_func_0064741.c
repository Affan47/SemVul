tz_info_from_location (TzLocation *loc)
{
	TzInfo *tzinfo;
	time_t curtime;
	struct tm *curzone;
	gchar *tz_env_value;

	g_return_val_if_fail (loc != NULL, NULL);
	g_return_val_if_fail (loc->zone != NULL, NULL);

	tz_env_value = g_strdup (getenv ("TZ"));
	setenv ("TZ", loc->zone, 1);

#if 0
	tzset ();
#endif
	tzinfo = g_new0 (TzInfo, 1);

	curtime = time (NULL);
	curzone = localtime (&curtime);

#ifndef __sun


	tzinfo->tzname_normal = g_strdup (curzone->tm_zone);
	if (curzone->tm_isdst)
		tzinfo->tzname_daylight =
			g_strdup (&curzone->tm_zone[curzone->tm_isdst]);
	else
		tzinfo->tzname_daylight = NULL;

	tzinfo->utc_offset = curzone->tm_gmtoff;
#else
	tzinfo->tzname_normal = NULL;
	tzinfo->tzname_daylight = NULL;
	tzinfo->utc_offset = 0;
#endif

	tzinfo->daylight = curzone->tm_isdst;

	if (tz_env_value)
		setenv ("TZ", tz_env_value, 1);
	else
		unsetenv ("TZ");

	g_free (tz_env_value);

	return tzinfo;
}
