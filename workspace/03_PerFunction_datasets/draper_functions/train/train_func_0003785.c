AtEOXact_UpdateFlatFiles(bool isCommit)
{
	Relation	drel = NULL;
	Relation	arel = NULL;
	Relation	mrel = NULL;

	if (database_file_update_subid == InvalidSubTransactionId &&
		auth_file_update_subid == InvalidSubTransactionId)
		return;

	if (!isCommit)
	{
		database_file_update_subid = InvalidSubTransactionId;
		auth_file_update_subid = InvalidSubTransactionId;
		return;
	}


	CommandCounterIncrement();


	if (database_file_update_subid != InvalidSubTransactionId)
		drel = heap_open(DatabaseRelationId, AccessShareLock);

	if (auth_file_update_subid != InvalidSubTransactionId)
	{
		arel = heap_open(AuthIdRelationId, AccessShareLock);
		mrel = heap_open(AuthMemRelationId, AccessShareLock);
	}


	if (database_file_update_subid != InvalidSubTransactionId)
		LockSharedObject(DatabaseRelationId, InvalidOid, 0,
						 AccessExclusiveLock);

	if (auth_file_update_subid != InvalidSubTransactionId)
		LockSharedObject(AuthIdRelationId, InvalidOid, 0,
						 AccessExclusiveLock);


	if (database_file_update_subid != InvalidSubTransactionId)
	{
		database_file_update_subid = InvalidSubTransactionId;
		write_database_file(drel, false);
		heap_close(drel, NoLock);
	}

	if (auth_file_update_subid != InvalidSubTransactionId)
	{
		auth_file_update_subid = InvalidSubTransactionId;
		write_auth_file(arel, mrel);
		heap_close(arel, NoLock);
		heap_close(mrel, NoLock);
	}


	SendPostmasterSignal(PMSIGNAL_PASSWORD_CHANGE);


	ForceSyncCommit();
}
