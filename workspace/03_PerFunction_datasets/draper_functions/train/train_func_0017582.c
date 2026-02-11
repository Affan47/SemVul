launcher_determine_sleep(bool canlaunch, bool recursing, struct timeval * nap)
{


	if (!canlaunch)
	{
		nap->tv_sec = autovacuum_naptime;
		nap->tv_usec = 0;
	}
	else if (!dlist_is_empty(&DatabaseList))
	{
		TimestampTz current_time = GetCurrentTimestamp();
		TimestampTz next_wakeup;
		avl_dbase  *avdb;
		long		secs;
		int			usecs;

		avdb = dlist_tail_element(avl_dbase, adl_node, &DatabaseList);

		next_wakeup = avdb->adl_next_worker;
		TimestampDifference(current_time, next_wakeup, &secs, &usecs);

		nap->tv_sec = secs;
		nap->tv_usec = usecs;
	}
	else
	{

		nap->tv_sec = autovacuum_naptime;
		nap->tv_usec = 0;
	}


	if (nap->tv_sec == 0 && nap->tv_usec == 0 && !recursing)
	{
		rebuild_database_list(InvalidOid);
		launcher_determine_sleep(canlaunch, true, nap);
		return;
	}


	if (nap->tv_sec <= 0 && nap->tv_usec <= MIN_AUTOVAC_SLEEPTIME * 1000)
	{
		nap->tv_sec = 0;
		nap->tv_usec = MIN_AUTOVAC_SLEEPTIME * 1000;
	}


	if (nap->tv_sec > MAX_AUTOVAC_SLEEPTIME)
		nap->tv_sec = MAX_AUTOVAC_SLEEPTIME;
}
