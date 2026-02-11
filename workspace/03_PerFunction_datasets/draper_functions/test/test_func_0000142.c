RelativeDate(time_t Start, time_t DayOrdinal, time_t DayNumber, int *error)
{
    struct tm	*tm;
    time_t	now;

    now = Start;
    tm = localtime(&now);
    if (tm == NULL) {
	*error = 1;
	return -1;
    }
    now += SECSPERDAY * ((DayNumber - tm->tm_wday + 7) % 7);
    now += 7 * SECSPERDAY * (DayOrdinal <= 0 ? DayOrdinal : DayOrdinal - 1);
    return DSTcorrect(Start, now, error);
}
