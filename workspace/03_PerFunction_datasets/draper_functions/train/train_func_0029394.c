gmtoff(tt)
time_t tt;
{
	struct tm lt;
#ifdef DONT_HAVE_TM_GMTOFF
	struct tm gt;
	time_t offset;

	lt=*localtime(&tt);
	gt=*gmtime(&tt);
	offset=gt.tm_yday-lt.tm_yday;
	if (offset > 1) offset=-24;
	else if (offset < -1) offset=24;
	else offset*=24;
	offset+=gt.tm_hour-lt.tm_hour;
	offset*=60;
	offset+=gt.tm_min-lt.tm_min;
	offset*=60;
	offset+=gt.tm_sec-lt.tm_sec;
	return offset;
#else
	lt=*localtime(&tt);
	return -lt.tm_gmtoff;
#endif
}
