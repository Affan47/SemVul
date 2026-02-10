WaitOnLock(LOCALLOCK *locallock, ResourceOwner owner)
{
	LOCKMETHODID lockmethodid = LOCALLOCK_LOCKMETHOD(*locallock);
	LockMethod	lockMethodTable = LockMethods[lockmethodid];
	char	   *volatile new_status = NULL;

	LOCK_PRINT("WaitOnLock: sleeping on lock",
			   locallock->lock, locallock->tag.mode);


	if (update_process_title)
	{
		const char *old_status;
		int			len;

		old_status = get_ps_display(&len);
		new_status = (char *) palloc(len + 8 + 1);
		memcpy(new_status, old_status, len);
		strcpy(new_status + len, " waiting");
		set_ps_display(new_status, false);
		new_status[len] = '\0';
	}
	pgstat_report_waiting(true);

	awaitedLock = locallock;
	awaitedOwner = owner;


	PG_TRY();
	{
		if (ProcSleep(locallock, lockMethodTable) != STATUS_OK)
		{


			awaitedLock = NULL;
			LOCK_PRINT("WaitOnLock: aborting on lock",
					   locallock->lock, locallock->tag.mode);
			LWLockRelease(LockHashPartitionLock(locallock->hashcode));


			DeadLockReport();

		}
	}
	PG_CATCH();
	{


		pgstat_report_waiting(false);
		if (update_process_title)
		{
			set_ps_display(new_status, false);
			pfree(new_status);
		}


		PG_RE_THROW();
	}
	PG_END_TRY();

	awaitedLock = NULL;


	pgstat_report_waiting(false);
	if (update_process_title)
	{
		set_ps_display(new_status, false);
		pfree(new_status);
	}

	LOCK_PRINT("WaitOnLock: wakeup on lock",
			   locallock->lock, locallock->tag.mode);
}
