add_string_date(const char *d)
{
	struct tm tm, *tmp;
	int n;
	time_t t;
	char *buf;
	int nbuf;
	char *env;

	memset(&tm, 0, sizeof(tm));
	n = sscanf(d, "%d.%d.%d.%d.%d.%d",
			&tm.tm_year, &tm.tm_mon, &tm.tm_mday,
			&tm.tm_hour, &tm.tm_min, &tm.tm_sec);
	tm.tm_mon--;
	if(tm.tm_year > 1900)
		tm.tm_year -= 1900;

	env = getenv("TZ");
	putenv("TZ=UTC0");
	t = mktime(&tm);
	if(env)
	{
		char *c = xmalloc(strlen(env) + 3 + 1);
		sprintf(c, "TZ=%s", env);
		putenv(c);
		xfree(c);
	}
	else
		putenv("TZ");

	if(n != 6 || t == (time_t)(-1))
	{
		add_string_str("<invalid date>");
		return;
	}

	tmp = localtime(&t);
	nbuf = (strlen(conf.date_format)+1) * 16;
	buf = xmalloc(nbuf);
	strftime(buf, nbuf, conf.date_format, tmp);
	add_string_str(buf);
	xfree(buf);
}
