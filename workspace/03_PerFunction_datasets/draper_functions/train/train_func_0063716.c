TruncateMultiXact(MultiXactId newOldestMulti, Oid newOldestMultiDB)
{
	MultiXactId oldestMulti;
	MultiXactId nextMulti;
	MultiXactOffset newOldestOffset;
	MultiXactOffset oldestOffset;
	MultiXactOffset nextOffset;
	mxtruncinfo trunc;
	MultiXactId earliest;

	Assert(!RecoveryInProgress());
	Assert(MultiXactState->finishedStartup);


	LWLockAcquire(MultiXactTruncationLock, LW_EXCLUSIVE);

	LWLockAcquire(MultiXactGenLock, LW_SHARED);
	nextMulti = MultiXactState->nextMXact;
	nextOffset = MultiXactState->nextOffset;
	oldestMulti = MultiXactState->oldestMultiXactId;
	LWLockRelease(MultiXactGenLock);
	Assert(MultiXactIdIsValid(oldestMulti));


	if (MultiXactIdPrecedesOrEquals(newOldestMulti, oldestMulti))
	{
		LWLockRelease(MultiXactTruncationLock);
		return;
	}


	trunc.earliestExistingPage = -1;
	SlruScanDirectory(MultiXactOffsetCtl, SlruScanDirCbFindEarliest, &trunc);
	earliest = trunc.earliestExistingPage * MULTIXACT_OFFSETS_PER_PAGE;
	if (earliest < FirstMultiXactId)
		earliest = FirstMultiXactId;


	if (MultiXactIdPrecedes(oldestMulti, earliest))
	{
		LWLockRelease(MultiXactTruncationLock);
		return;
	}


	if (oldestMulti == nextMulti)
	{

		oldestOffset = nextOffset;
	}
	else if (!find_multixact_start(oldestMulti, &oldestOffset))
	{
		ereport(LOG,
				(errmsg("oldest MultiXact %u not found, earliest MultiXact %u, skipping truncation",
						oldestMulti, earliest)));
		LWLockRelease(MultiXactTruncationLock);
		return;
	}


	if (newOldestMulti == nextMulti)
	{

		newOldestOffset = nextOffset;
	}
	else if (!find_multixact_start(newOldestMulti, &newOldestOffset))
	{
		ereport(LOG,
				(errmsg("cannot truncate up to MultiXact %u because it does not exist on disk, skipping truncation",
						newOldestMulti)));
		LWLockRelease(MultiXactTruncationLock);
		return;
	}

	elog(DEBUG1, "performing multixact truncation: "
		 "offsets [%u, %u), offsets segments [%x, %x), "
		 "members [%u, %u), members segments [%x, %x)",
		 oldestMulti, newOldestMulti,
		 MultiXactIdToOffsetSegment(oldestMulti),
		 MultiXactIdToOffsetSegment(newOldestMulti),
		 oldestOffset, newOldestOffset,
		 MXOffsetToMemberSegment(oldestOffset),
		 MXOffsetToMemberSegment(newOldestOffset));


	START_CRIT_SECTION();


	Assert(!MyPgXact->delayChkpt);
	MyPgXact->delayChkpt = true;


	WriteMTruncateXlogRec(newOldestMultiDB,
						  oldestMulti, newOldestMulti,
						  oldestOffset, newOldestOffset);


	LWLockAcquire(MultiXactGenLock, LW_EXCLUSIVE);
	MultiXactState->oldestMultiXactId = newOldestMulti;
	MultiXactState->oldestMultiXactDB = newOldestMultiDB;
	LWLockRelease(MultiXactGenLock);


	PerformMembersTruncation(oldestOffset, newOldestOffset);


	PerformOffsetsTruncation(oldestMulti, newOldestMulti);

	MyPgXact->delayChkpt = false;

	END_CRIT_SECTION();
	LWLockRelease(MultiXactTruncationLock);
}
