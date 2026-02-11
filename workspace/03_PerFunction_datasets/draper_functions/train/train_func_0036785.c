time_tic_just(t_timelevel level, double ticplace)
{
    struct tm tm;

    if (level <= TIMELEVEL_SECONDS) {
	return (ticplace);
    }
    ggmtime(&tm, ticplace);
    if (level >= TIMELEVEL_MINUTES) {
	if (tm.tm_sec > 55)
	    tm.tm_min++;
	tm.tm_sec = 0;
    }
    if (level >= TIMELEVEL_HOURS) {
	if (tm.tm_min > 55)
	    tm.tm_hour++;
	tm.tm_min = 0;
    }
    if (level >= TIMELEVEL_DAYS) {
	if (tm.tm_hour > 22) {
	    tm.tm_hour = 0;
	    tm.tm_mday = 0;
	    tm.tm_yday++;
	    ggmtime(&tm, gtimegm(&tm));
	}
    }

    if (level >= TIMELEVEL_MONTHS) {
	if (tm.tm_mday > 25) {
	    tm.tm_mon++;
	    if (tm.tm_mon > 11) {
		tm.tm_year++;
		tm.tm_mon = 0;
	    }
	}
	tm.tm_mday = 1;
    }

    ticplace = gtimegm(&tm);
    return (ticplace);
}
