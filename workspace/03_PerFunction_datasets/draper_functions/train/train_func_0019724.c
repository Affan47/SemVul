file_fmttime(uint32_t v, int local)
{
	char *pp;
	time_t t = (time_t)v;
	struct tm *tm;

	if (local) {
		pp = ctime(&t);
	} else {
#ifndef HAVE_DAYLIGHT
		private int daylight = 0;
#ifdef HAVE_TM_ISDST
		private time_t now = (time_t)0;

		if (now == (time_t)0) {
			struct tm *tm1;
			(void)time(&now);
			tm1 = localtime(&now);
			if (tm1 == NULL)
				return "*Invalid time*";
			daylight = tm1->tm_isdst;
		}
#endif
#endif
		if (daylight)
			t += 3600;
		tm = gmtime(&t);
		if (tm == NULL)
			return "*Invalid time*";
		pp = asctime(tm);
	}

	pp[strcspn(pp, "\n")] = '\0';
	return pp;
}
