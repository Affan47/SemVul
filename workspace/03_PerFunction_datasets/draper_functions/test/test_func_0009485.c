CdDayOfYear(CdTime *date, int *doy)
{
	int leap_add = 0;
	int month;
	long year;

   	month	= date->month;
	if (month < 1 || month > 12) {
		cdError( "Day-of-year error; month: %d\n", month);
		month = 1;
	}

	if(!(date->timeType & CdChronCal))
		year = 0;
	else if(!(date->timeType & CdBase1970))
		year = date->baseYear + date->year;
	else
		year = date->year;

	if (ISLEAP(year,date->timeType) && month > 2) leap_add = 1;
	if( ((date->timeType) & Cd365) || ((date->timeType) & Cd366) ) {
	    *doy = days_sum[month-1] + date->day + leap_add ;
	} else {
	    *doy = 30*(month-1) + date->day + leap_add ;
	}
	return;
}
