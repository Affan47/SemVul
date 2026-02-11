Cdh2e(CdTime *htime, double *etime)
{
	long 	ytemp, year;
	int	day_cnt;
	int 	doy;
	long    baseYear;
	int     daysInLeapYear;
	int     daysInYear;
	extern void CdDayOfYear(CdTime *date, int *doy);

	CdDayOfYear(htime,&doy);

	day_cnt	= 0;

	baseYear = ((htime->timeType) & CdBase1970) ? 1970 : htime->baseYear;
	year = ((htime->timeType) & CdBase1970) ? htime->year : (htime->year + htime->baseYear);
	if(!((htime->timeType) & CdChronCal)) baseYear = year = 0;
	daysInLeapYear = ((htime->timeType) & Cd365) ? 366 : 360;
	daysInYear = ((htime->timeType) & Cd365) ? 365 : 360;

	if (year > baseYear) {
		for (ytemp = year - 1; ytemp >= baseYear; ytemp--) {
			day_cnt += ISLEAP(ytemp,htime->timeType) ? daysInLeapYear : daysInYear;
		}
	} else if (year < baseYear) {
		for (ytemp = year; ytemp < baseYear; ytemp++) {
			day_cnt -= ISLEAP(ytemp,htime->timeType) ? daysInLeapYear : daysInYear;
		}
	}
	*etime	= (double) (day_cnt + doy - 1) * 24. + htime->hour;
        return;
}
