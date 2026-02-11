php_std_date(time_t t TSRMLS_DC)
{
	struct tm *tm1, tmbuf;
	char *str;

	tm1 = php_gmtime_r(&t, &tmbuf);
	str = emalloc(81);
	str[0] = '\0';

	if (!tm1) {
		return str;
	}

	snprintf(str, 80, "%s, %02d %s %04d %02d:%02d:%02d GMT",
			day_short_names[tm1->tm_wday],
			tm1->tm_mday,
			mon_short_names[tm1->tm_mon],
			tm1->tm_year + 1900,
			tm1->tm_hour, tm1->tm_min, tm1->tm_sec);

	str[79] = 0;
	return (str);
}
