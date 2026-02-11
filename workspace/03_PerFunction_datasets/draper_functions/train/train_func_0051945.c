get_delta (int       src,
	   int       dest,
	   GTimeVal *start_time,
	   GTimeVal *end_time,
	   GTimeVal *cur_time)
{
	double x, s, n, d, percentage;

	s = start_time->tv_sec + ((double)start_time->tv_usec / G_USEC_PER_SEC);
	n = cur_time->tv_sec + ((double)cur_time->tv_usec / G_USEC_PER_SEC);
	d = end_time->tv_sec + ((double)end_time->tv_usec / G_USEC_PER_SEC);

	n -= s;
	d -= s;

	if (abs (dest - src) <= 1 || n >= d)
		return dest - src;


	x = (double)n/d;
	x = -2 * (x*x) * (x-1.5);

	percentage = -2 * (x*x) * (x-1.5);

	percentage = CLAMP (percentage, 0.0, 1.0);

	return ((dest - src) * percentage);
}
