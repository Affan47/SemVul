isCacheValid(struct tm cached)
{
	struct timeval tv;
	struct timezone tz;
	double offset = 0;
	time_t now = 0;
	time_t cache = 0;
	double diff = 0;

	gettimeofday(&tv, &tz);
	offset = (double)(tz.tz_minuteswest * 60);
	now = time(NULL);
	cache = mktime(&cached);
	diff = difftime(cache, now);

	if (diff < offset)
		return 0;
	else
		return 1;
}
