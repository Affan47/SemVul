timestampToParts( TTimeStamp t, TTimeParts &p , bool localTime)
{
	double T = mrpt::system::timestampTotime_t(t);
	time_t tt = time_t(T);

	double sec_frac = T - uint64_t(tt);
	ASSERT_(sec_frac<1.0);

	struct tm * parts =  localTime ? localtime(&tt) : gmtime(&tt);
	ASSERTMSG_(parts, "Malformed timestamp");

	p.year		= parts->tm_year + 1900;
	p.month		= parts->tm_mon + 1;
	p.day		= parts->tm_mday;
	p.day_of_week = parts->tm_wday + 1;
	p.daylight_saving = parts->tm_isdst;
	p.hour		= parts->tm_hour;
	p.minute	= parts->tm_min;
	p.second	= parts->tm_sec + sec_frac;
}
