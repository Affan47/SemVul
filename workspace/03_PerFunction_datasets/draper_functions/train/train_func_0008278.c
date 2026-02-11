add_week(time_t n, unsigned cnt)
{
	struct tm *tmptr=localtime(&n);
	struct tm tmsave= *tmptr;

	if (!tmptr)
		return (0);

	tmptr->tm_hour=13;
	tmptr->tm_min=0;
	tmptr->tm_sec=0;

	n=mktime(tmptr);

	if (n == (time_t)-1)
		return (0);

	n += cnt * 7 * 24 * 60 * 60;

	tmptr=localtime(&n);

	tmptr->tm_hour=tmsave.tm_hour;
	tmptr->tm_min=tmsave.tm_min;
	tmptr->tm_sec=tmsave.tm_sec;

	n=mktime(tmptr);
	if (n == (time_t)-1)
		return (0);
	return (n);
}
