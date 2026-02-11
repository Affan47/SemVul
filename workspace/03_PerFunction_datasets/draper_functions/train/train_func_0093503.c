vboxrc_return_timestr(time_t timeint, char *timestr)
{
	struct tm *tm;

	if ((tm = localtime(&timeint)))
	{
		if (strftime(timestr, 20, "%H:%M:%S", tm) == 8) return;
	}

	xstrncpy(timestr, "??:??:??", 8);
}
