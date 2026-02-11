Cde2h(double etime, CdTimeType timeType, long baseYear, CdTime *htime)
{
	long 	ytemp;
	int 	yr_day_cnt;
	int 	doy;
	int     daysInLeapYear;
	int     daysInYear;
	extern void CdMonthDay(int *doy, CdTime *date);

	doy	= (long) floor(etime / 24.) + 1;
	htime->hour	= etime - (double) (doy - 1) * 24.;


	if(htime->hour >= 24.){
		doy += 1;
		htime->hour -= 24.;
	}

	htime->baseYear = (timeType & CdBase1970) ? 1970 : baseYear;
	if(!(timeType & CdChronCal)) htime->baseYear = 0;
	if(timeType & Cd366) {
	    daysInLeapYear = 366;
	    daysInYear = 366;
	} else {
	    daysInLeapYear = (timeType & Cd365) ? 366 : 360;
	    daysInYear = (timeType & Cd365) ? 365 : 360;
	}

	if (doy > 0) {
		for (ytemp = htime->baseYear; ; ytemp++) {
			yr_day_cnt = ISLEAP(ytemp,timeType) ? daysInLeapYear : daysInYear;
			if (doy <= yr_day_cnt) break;
			doy -= yr_day_cnt;
		}
	} else {
		for (ytemp = htime->baseYear-1; ; ytemp--) {
			yr_day_cnt = ISLEAP(ytemp,timeType) ? daysInLeapYear : daysInYear;
			doy += yr_day_cnt;
			if (doy > 0) break;
		}
	}
        htime->year = (timeType & CdBase1970) ? ytemp : (ytemp - htime->baseYear);
	if(!(timeType & CdChronCal)) htime->year = 0;
	htime->timeType = timeType;
	CdMonthDay(&doy,htime);

        return;
}
