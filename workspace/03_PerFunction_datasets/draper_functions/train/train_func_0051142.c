cdComp2Char(cdCalenType timetype, cdCompTime comptime, char* time)
{
	double dtmp, sec;
	int ihr, imin;
	int nskip;

	if(cdValidateTime(timetype,comptime))
		return;

	ihr = (int)comptime.hour;
	dtmp = 60.0 * (comptime.hour - (double)ihr);
	imin = (int)dtmp;
	sec = 60.0 * (dtmp - (double)imin);

	nskip = 0;
	if(sec == 0.0){
		if(imin == 0)
			nskip = 2;
		else
			nskip = 1;
	}

	if(timetype & cdStandardCal){
		if(nskip == 0)
			sprintf(time,"%ld-%hd-%hd %d:%d:%lf",comptime.year,comptime.month,comptime.day,ihr,imin,sec);
		else if(nskip == 1)
			sprintf(time,"%ld-%hd-%hd %d:%d",comptime.year,comptime.month,comptime.day,ihr,imin);
		else
			sprintf(time,"%ld-%hd-%hd %d:0",comptime.year,comptime.month,comptime.day,ihr);
	}
	else {
		if(nskip == 0)
			sprintf(time,"%hd-%hd %d:%d:%lf",comptime.month,comptime.day,ihr,imin,sec);
		else if(nskip == 1)
			sprintf(time,"%hd-%hd %d:%d",comptime.month,comptime.day,ihr,imin);
		else
			sprintf(time,"%hd-%hd %d:0",comptime.month,comptime.day,ihr);
	}
	return;
}
