GetLockStatusData(void)
{
	LockData   *data;
	PROCLOCK   *proclock;
	HASH_SEQ_STATUS seqstat;
	int			els;
	int			el;
	int			i;

	data = (LockData *) palloc(sizeof(LockData));


	for (i = 0; i < NUM_LOCK_PARTITIONS; i++)
		LWLockAcquire(FirstLockMgrLock + i, LW_SHARED);


	els = hash_get_num_entries(LockMethodProcLockHash);

	data->nelements = els;
	data->proclocks = (PROCLOCK *) palloc(sizeof(PROCLOCK) * els);
	data->procs = (PGPROC *) palloc(sizeof(PGPROC) * els);
	data->locks = (LOCK *) palloc(sizeof(LOCK) * els);


	hash_seq_init(&seqstat, LockMethodProcLockHash);

	el = 0;
	while ((proclock = (PROCLOCK *) hash_seq_search(&seqstat)))
	{
		PGPROC	   *proc = proclock->tag.myProc;
		LOCK	   *lock = proclock->tag.myLock;

		memcpy(&(data->proclocks[el]), proclock, sizeof(PROCLOCK));
		memcpy(&(data->procs[el]), proc, sizeof(PGPROC));
		memcpy(&(data->locks[el]), lock, sizeof(LOCK));

		el++;
	}


	for (i = NUM_LOCK_PARTITIONS; --i >= 0;)
		LWLockRelease(FirstLockMgrLock + i);

	Assert(el == data->nelements);

	return data;
}
