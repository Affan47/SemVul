print_tztime(struct text_object *obj, char *p, int p_max_size)
{
	char *oldTZ = NULL;
	time_t t;
	struct tm *tm;
	struct tztime_s *ts = obj->data.opaque;

	if (!ts)
		return;

	if (ts->tz) {
		oldTZ = getenv("TZ");
		setenv("TZ", ts->tz, 1);
		tzset();
	}
	t = time(NULL);
	tm = localtime(&t);

	setlocale(LC_TIME, "");
	strftime(p, p_max_size, ts->fmt, tm);
	if (oldTZ) {
		setenv("TZ", oldTZ, 1);
		tzset();
	} else {
		unsetenv("TZ");
	}

}
