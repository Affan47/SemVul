timestamp()
{
	static char buf[80];
	static time_t saveTime = 0;
	time_t t = time(0);

	if (t != saveTime) {
		struct tm *tmp = localtime(&t);

		strftime(buf, (size_t)sizeof(buf), "%c", tmp);
		saveTime = t;
	}
	return buf;
}
