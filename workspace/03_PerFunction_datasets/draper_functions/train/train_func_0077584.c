amiga_to_timeval (struct mytimeval *tv, int days, int mins, int ticks)
{
	uae_s64 t;

	if (days < 0)
		days = 0;
	if (days > 9900 * 365)
		days = 9900 * 365;
	if (mins < 0 || mins >= 24 * 60)
		mins = 0;
	if (ticks < 0 || ticks >= 60 * 50)
		ticks = 0;

	t = ticks * 20;
	t += mins * (60 * 1000);
	t += ((uae_u64)days) * msecs_per_day;
	t += diff;

	tv->tv_sec = t / 1000;
	tv->tv_usec = (t % 1000) * 1000;
}
