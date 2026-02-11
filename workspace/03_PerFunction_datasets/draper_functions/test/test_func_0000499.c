ast_say_date_pt(struct ast_channel *chan, time_t t, const char *ints, const char *lang)
{
	struct timeval when = { t, 0 };
	struct ast_tm tm;
	char fn[256];
	int res = 0;

	ast_localtime(&when, &tm, NULL);
	snprintf(fn, sizeof(fn), "digits/day-%d", tm.tm_wday);
	if (!res)
		res = wait_file(chan, ints, fn, lang);
	if (!res)
		res = ast_say_number(chan, tm.tm_mday, ints, lang, (char *) NULL);
	if (!res)
		res = wait_file(chan, ints, "digits/pt-de", lang);
	snprintf(fn, sizeof(fn), "digits/mon-%d", tm.tm_mon);
	if (!res)
		res = wait_file(chan, ints, fn, lang);
	if (!res)
		res = wait_file(chan, ints, "digits/pt-de", lang);
	if (!res)
		res = ast_say_number(chan, tm.tm_year + 1900, ints, lang, (char *) NULL);

	return res;
}
