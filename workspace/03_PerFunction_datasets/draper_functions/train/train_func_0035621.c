interval_string(unsigned int secs)
{
	static char buf[256], tmp[80];
	int		hr, min, num;

	buf[0] = 0;

	if (secs == 0)
		return "<none>";

	if (secs >= MONTH_INT) {
		num = secs / MONTH_INT;
		secs -= num*MONTH_INT;
		sprintf(buf, "%d month%s", num, (num>1) ? "s" : "");
	}
	if (secs >= WEEK_INT) {
		num = secs / WEEK_INT;
		secs -= num*WEEK_INT;
		sprintf(tmp, "%s%d week%s", buf[0] ? ", " : "",
			num, (num>1) ? "s" : "");
		strcat(buf, tmp);
	}
	if (secs >= DAY_INT) {
		num = secs / DAY_INT;
		secs -= num*DAY_INT;
		sprintf(tmp, "%s%d day%s", buf[0] ? ", " : "",
			num, (num>1) ? "s" : "");
		strcat(buf, tmp);
	}
	if (secs > 0) {
		hr = secs / HOUR_INT;
		secs -= hr*HOUR_INT;
		min = secs / MINUTE_INT;
		secs -= min*MINUTE_INT;
		sprintf(tmp, "%s%d:%02d:%02d", buf[0] ? ", " : "",
			hr, min, secs);
		strcat(buf, tmp);
	}
	return buf;
}
