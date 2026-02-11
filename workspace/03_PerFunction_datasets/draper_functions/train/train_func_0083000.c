GetTime(long timeNow, TIMER * pTimerLocate, long *time, long defaultTime)
{

	long lOffset = 0;
	char onLocated = 0;
	TIMER *pTimer;


	if (pTimerLocate && pTimerLocate->pointer != NULL) {
		lOffset = 0;
		pTimer = pTimerLocate;

		onLocated = FindNextToday(timeNow, pTimer, time);


		if (0 == onLocated) {
			pTimer = pTimerLocate;
			onLocated =
			    FindNextDay(timeNow, pTimer, time, &lOffset);
		}


		if (0 == onLocated) {
			*time = pTimerLocate->time;
			lOffset =
			    ((6 - last_day) +
			     pTimerLocate->day) * TWENTYFOURHR;
		}

		*time += lOffset;

		if (lOffset > TWENTYFOURHR && defaultTime > 0)
			*time = defaultTime;
	} else
		*time = defaultTime;
}
