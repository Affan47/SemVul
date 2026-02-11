jabber_try_xdelay(const char *stamp) {

	if (stamp) {
		struct tm tm;
		char *tmp = xstrdup(getenv("TZ"));
		time_t out;

		memset(&tm, 0, sizeof(tm));
		sscanf(stamp, "%4d%2d%2dT%2d:%2d:%2d",
				&tm.tm_year, &tm.tm_mon, &tm.tm_mday,
				&tm.tm_hour, &tm.tm_min, &tm.tm_sec);
		tm.tm_year -= 1900;
		tm.tm_mon -= 1;

		setenv("TZ", "UTC", 1);
		out = mktime(&tm);
		if (tmp)
			setenv("TZ", tmp, 1);
		else
			unsetenv("TZ");
		xfree(tmp);

		return out;
	}
	return time(NULL);

}
