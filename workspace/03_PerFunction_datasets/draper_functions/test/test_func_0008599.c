ntable_strtime_delta(__u32 msec)
{
	static char str[32];
	struct timeval now;
	time_t t;
	struct tm *tp;

	if (msec == 0)
		goto error;

	memset(&now, 0, sizeof(now));

	if (gettimeofday(&now, NULL) < 0) {
		perror("gettimeofday");
		goto error;
	}

	t = now.tv_sec - (msec / 1000);
	tp = localtime(&t);
	if (!tp)
		goto error;

	strftime(str, sizeof(str), "%Y-%m-%d %T", tp);

	return str;
 error:
	strcpy(str, "(error)");
	return str;
}
