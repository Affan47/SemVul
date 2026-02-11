Xtimegm(tm)
CONST struct tm *tm;
{
	time_t t;
	int i, y;

	if (tm -> tm_year < 0) return((time_t)-1);
	y = (tm -> tm_year < 1900) ? tm -> tm_year + 1900 : tm -> tm_year;
	if (tm -> tm_mon < 0 || tm -> tm_mon > 11) return((time_t)-1);
	if (tm -> tm_mday < 1
	|| tm -> tm_mday > getmaxday(tm -> tm_mon + 1, y))
		return((time_t)-1);
	if (tm -> tm_hour < 0 || tm -> tm_hour > 23) return((time_t)-1);
	if (tm -> tm_min < 0 || tm -> tm_min > 59) return((time_t)-1);
	if (tm -> tm_sec < 0 || tm -> tm_sec > 60) return((time_t)-1);

	t = ((long)y - 1970) * 365;
	t += ((y - 1 - 1968) / 4)
		- ((y - 1 - 1900) / 100)
		+ ((y - 1 - 1600) / 400);
	for (i = 1; i < tm -> tm_mon + 1; i++) t += getmaxday(i, y);
	t += tm -> tm_mday - 1;
	t *= 60L * 60L * 24L;
	t += ((long)(tm -> tm_hour) * 60L + tm -> tm_min) * 60L + tm -> tm_sec;

	return(t);
}
