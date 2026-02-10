localTime(const Date& date, hourTy h, minuteTy m, secondTy s)


{
	clockTy t = (seconds_in_day*(date-refDate) + 60L*60L*h + 60L*m + s);
	if ( !date.between(refDate,maxDate) || (TIME_ZONE < 0 && t < -TIME_ZONE) )
	    fprintf(stderr,"Date range error %d %s %d\n", date.dayOfMonth(),date.nameOfMonth(),date.year());

	return Time(t);
}
