log_get_rotationsyncclock(int synchour, int syncmin)
{
	struct tm	*currtm;
	time_t		currclock;
	time_t		syncclock;
	int			hours, minutes;

	time( &currclock);
	currtm = localtime( &currclock );

	if ( syncmin < currtm->tm_min ) {
		minutes = syncmin + 60 - currtm->tm_min;
		hours = synchour - 1 - currtm->tm_hour;
	} else {
		minutes = syncmin - currtm->tm_min;
		hours = synchour - currtm->tm_hour;
	}
	if ( hours < 0 ) hours += 24;

	syncclock = currclock + hours * 3600 + minutes * 60;
	return syncclock;
}
