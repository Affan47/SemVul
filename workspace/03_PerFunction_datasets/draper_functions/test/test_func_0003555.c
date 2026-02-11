InitLocks(void)
{
	HASHCTL		info;
	int			hash_flags;
	long		init_table_size,
				max_table_size;


	max_table_size = NLOCKENTS();
	init_table_size = max_table_size / 2;


	MemSet(&info, 0, sizeof(info));
	info.keysize = sizeof(LOCKTAG);
	info.entrysize = sizeof(LOCK);
	info.hash = tag_hash;
	info.num_partitions = NUM_LOCK_PARTITIONS;
	hash_flags = (HASH_ELEM | HASH_FUNCTION | HASH_PARTITION);

	LockMethodLockHash = ShmemInitHash("LOCK hash",
									   init_table_size,
									   max_table_size,
									   &info,
									   hash_flags);
	if (!LockMethodLockHash)
		elog(FATAL, "could not initialize lock hash table");


	max_table_size *= 2;
	init_table_size *= 2;


	info.keysize = sizeof(PROCLOCKTAG);
	info.entrysize = sizeof(PROCLOCK);
	info.hash = proclock_hash;
	info.num_partitions = NUM_LOCK_PARTITIONS;
	hash_flags = (HASH_ELEM | HASH_FUNCTION | HASH_PARTITION);

	LockMethodProcLockHash = ShmemInitHash("PROCLOCK hash",
										   init_table_size,
										   max_table_size,
										   &info,
										   hash_flags);
	if (!LockMethodProcLockHash)
		elog(FATAL, "could not initialize proclock hash table");


	if (LockMethodLocalHash)
		hash_destroy(LockMethodLocalHash);

	info.keysize = sizeof(LOCALLOCKTAG);
	info.entrysize = sizeof(LOCALLOCK);
	info.hash = tag_hash;
	hash_flags = (HASH_ELEM | HASH_FUNCTION);

	LockMethodLocalHash = hash_create("LOCALLOCK hash",
									  128,
									  &info,
									  hash_flags);
}
