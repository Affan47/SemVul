timestamp_rfc1123_to_string_buf(time_t date, char *buf, size_t size)
{
	const struct tm *tm;

	g_assert(size > 0);
	tm = gmtime(&date);
	return str_bprintf(buf, size, "%s, %02d %s %04d %02d:%02d:%02d GMT",
		days[tm->tm_wday], tm->tm_mday, months[tm->tm_mon], tm->tm_year + 1900,
		tm->tm_hour, tm->tm_min, tm->tm_sec);
}
