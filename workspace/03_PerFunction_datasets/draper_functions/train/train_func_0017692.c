ac_get_yweek(struct tm* _tm)
{
	int week = -1;
#ifdef USE_YWEEK_V
	int days;
#endif

	if(!_tm)
		return -1;

#ifdef USE_YWEEK_U
	week = SUN_WEEK(_tm);
#else
	week = MON_WEEK(_tm);
#endif

#ifdef USE_YWEEK_V
	days = ((_tm->tm_yday + 7 - (_tm->tm_wday ? _tm->tm_wday-1 : 6)) % 7);

	if(days >= 4)
		week++;
	else
		if(week == 0)
			week = 53;
#endif
	return week;
}
