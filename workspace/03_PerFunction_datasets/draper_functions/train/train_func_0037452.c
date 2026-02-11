http_timestamp(time_t t) {
	static char buf[2][100];
	struct tm *tm = localtime(&t);
	static int i = 0;

	const char *format = format_find("timestamp");

	if (!format)
		return itoa(t);

	i = i % 2;
	if (!strftime(buf[i], sizeof(buf[0]), format, tm) && xstrlen(format)>0)
		xstrcpy(buf[i], "TOOLONG");
	return buf[i++];
}
