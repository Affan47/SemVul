FindNextDay(long timeNow, TIMER * pTimer, long *time, long *offset)
{

	int iLocated = 0;

	while (pTimer != NULL && pTimer->pointer != NULL) {

		if (pTimer->day > last_day) {

			if (pTimer->day > last_day)
				*offset =
				    (pTimer->day -
				     last_day) * TWENTYFOURHR;

			iLocated = 1;
			*time = pTimer->time;
			pTimer = NULL;
		} else {
			pTimer = pTimer->pointer;
		}
	}

	return iLocated;
}
