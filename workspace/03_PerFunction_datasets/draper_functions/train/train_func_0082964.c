sms_scts_to_time(const struct sms_scts *scts, struct tm *remote)
{
	struct tm t;
	time_t ret;

	t.tm_sec = scts->second;
	t.tm_min = scts->minute;
	t.tm_hour = scts->hour;
	t.tm_mday = scts->day;
	t.tm_mon = scts->month - 1;
	t.tm_isdst = -1;

	if (scts->year > 80)
		t.tm_year = scts->year;
	else
		t.tm_year = scts->year + 100;

	ret = mktime(&t);


	ret += t.tm_gmtoff;


	t.tm_gmtoff = scts->timezone * 15 * 60;


	ret -= t.tm_gmtoff;

	if (remote)
		memcpy(remote, &t, sizeof(struct tm));

	return ret;
}
