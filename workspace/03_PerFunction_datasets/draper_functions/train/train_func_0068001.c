cgit_print_date(time_t secs, char *format, int local_time)
{
	char buf[64];
	struct tm *time;

	if (!secs)
		return;
	if(local_time)
		time = localtime(&secs);
	else
		time = gmtime(&secs);
	strftime(buf, sizeof(buf)-1, format, time);
	html_txt(buf);
}
