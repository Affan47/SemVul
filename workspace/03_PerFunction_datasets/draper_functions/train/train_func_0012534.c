do_start_worker(void)
{
	List	   *dblist;
	ListCell   *cell;
	TransactionId xidForceLimit;
	bool		for_xid_wrap;
	avw_dbase  *avdb;
	TimestampTz current_time;
	bool		skipit = false;
	Oid			retval = InvalidOid;
	MemoryContext tmpcxt,
				oldcxt;


	LWLockAcquire(AutovacuumLock, LW_SHARED);
	if (AutoVacuumShmem->av_freeWorkers == INVALID_OFFSET)
	{
		LWLockRelease(AutovacuumLock);
		return InvalidOid;
	}
	LWLockRelease(AutovacuumLock);


	tmpcxt = AllocSetContextCreate(CurrentMemoryContext,
								   "Start worker tmp cxt",
								   ALLOCSET_DEFAULT_MINSIZE,
								   ALLOCSET_DEFAULT_INITSIZE,
								   ALLOCSET_DEFAULT_MAXSIZE);
	oldcxt = MemoryContextSwitchTo(tmpcxt);


	autovac_refresh_stats();


	dblist = get_database_list();


	recentXid = ReadNewTransactionId();
	xidForceLimit = recentXid - autovacuum_freeze_max_age;

	if (xidForceLimit < FirstNormalTransactionId)
		xidForceLimit -= FirstNormalTransactionId;


	avdb = NULL;
	for_xid_wrap = false;
	current_time = GetCurrentTimestamp();
	foreach(cell, dblist)
	{
		avw_dbase  *tmp = lfirst(cell);
		Dlelem	   *elem;


		if (TransactionIdPrecedes(tmp->adw_frozenxid, xidForceLimit))
		{
			if (avdb == NULL ||
			  TransactionIdPrecedes(tmp->adw_frozenxid, avdb->adw_frozenxid))
				avdb = tmp;
			for_xid_wrap = true;
			continue;
		}
		else if (for_xid_wrap)
			continue;


		tmp->adw_entry = pgstat_fetch_stat_dbentry(tmp->adw_datid);


		if (!tmp->adw_entry)
			continue;


		skipit = false;
		elem = DatabaseList ? DLGetTail(DatabaseList) : NULL;

		while (elem != NULL)
		{
			avl_dbase  *dbp = DLE_VAL(elem);

			if (dbp->adl_datid == tmp->adw_datid)
			{


				if (!TimestampDifferenceExceeds(dbp->adl_next_worker,
												current_time, 0) &&
					!TimestampDifferenceExceeds(current_time,
												dbp->adl_next_worker,
												autovacuum_naptime * 1000))
					skipit = true;

				break;
			}
			elem = DLGetPred(elem);
		}
		if (skipit)
			continue;


		if (avdb == NULL ||
			tmp->adw_entry->last_autovac_time < avdb->adw_entry->last_autovac_time)
			avdb = tmp;
	}


	if (avdb != NULL)
	{
		WorkerInfo	worker;
		SHMEM_OFFSET sworker;

		LWLockAcquire(AutovacuumLock, LW_EXCLUSIVE);


		sworker = AutoVacuumShmem->av_freeWorkers;
		if (sworker == INVALID_OFFSET)
			elog(FATAL, "no free worker found");

		worker = (WorkerInfo) MAKE_PTR(sworker);
		AutoVacuumShmem->av_freeWorkers = worker->wi_links.next;

		worker->wi_dboid = avdb->adw_datid;
		worker->wi_proc = NULL;
		worker->wi_launchtime = GetCurrentTimestamp();

		AutoVacuumShmem->av_startingWorker = sworker;

		LWLockRelease(AutovacuumLock);

		SendPostmasterSignal(PMSIGNAL_START_AUTOVAC_WORKER);

		retval = avdb->adw_datid;
	}
	else if (skipit)
	{


		rebuild_database_list(InvalidOid);
	}

	MemoryContextSwitchTo(oldcxt);
	MemoryContextDelete(tmpcxt);

	return retval;
}
