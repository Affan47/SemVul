VTIM_parse(const char *p)
{
	double t;
	struct tm tm;
	const char **r;

	for (r = fmts; *r != NULL; r++) {
		memset(&tm, 0, sizeof tm);
		if (strptime(p, *r, &tm) != NULL) {


			tm.tm_isdst = -1;
#if defined(HAVE_TIMEGM)
			t = timegm(&tm);
#else


			t = mktime(&tm);
			assert(!strcmp(tzname[0], "UTC"));
#endif
			return (t);
		}
	}
	return (0);
}
