ast_say_datetime_zh(struct ast_channel *chan, time_t t, const char *ints, const char *lang)
{
	struct timeval when = { t, 0 };
	struct ast_tm tm;
	char fn[256];
	int res = 0;
	int hour, pm=0;

	ast_localtime(&when, &tm, NULL);
	if (!res)
		res = ast_say_number(chan, tm.tm_year + 1900, ints, lang, (char *) NULL);
	if (!res) {
		snprintf(fn, sizeof(fn), "digits/mon-%d", tm.tm_mon);
		res = ast_streamfile(chan, fn, lang);
		if (!res)
			res = ast_waitstream(chan, ints);
	}
	if (!res)
		res = ast_say_number(chan, tm.tm_mday, ints, lang, (char *) NULL);
	if (!res) {
		snprintf(fn, sizeof(fn), "digits/day-%d", tm.tm_wday);
		res = ast_streamfile(chan, fn, lang);
		if (!res)
			res = ast_waitstream(chan, ints);
	}

	hour = tm.tm_hour;
	if (!hour)
		hour = 12;
	else if (hour == 12)
		pm = 1;
	else if (hour > 12) {
		hour -= 12;
		pm = 1;
	}
	if (pm) {
		if (!res)
			res = ast_streamfile(chan, "digits/p-m", lang);
	} else {
		if (!res)
			res = ast_streamfile(chan, "digits/a-m", lang);
	}
	if (!res)
		res = ast_waitstream(chan, ints);
	if (!res)
		res = ast_say_number(chan, hour, ints, lang, (char *) NULL);
	if (!res)
		res = ast_streamfile(chan, "digits/oclock", lang);
	if (!res)
		res = ast_waitstream(chan, ints);
	if (!res)
		res = ast_say_number(chan, tm.tm_min, ints, lang, (char *) NULL);
	if (!res)
		res = ast_streamfile(chan, "digits/minute", lang);
	if (!res)
		res = ast_waitstream(chan, ints);
	return res;
}
