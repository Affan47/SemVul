xact_redo_commit(xl_xact_parsed_commit *parsed,
				 TransactionId xid,
				 XLogRecPtr lsn,
				 RepOriginId origin_id)
{
	TransactionId max_xid;
	int			i;
	TimestampTz commit_time;

	max_xid = TransactionIdLatest(xid, parsed->nsubxacts, parsed->subxacts);


	if (TransactionIdFollowsOrEquals(max_xid,
									 ShmemVariableCache->nextXid))
	{
		LWLockAcquire(XidGenLock, LW_EXCLUSIVE);
		ShmemVariableCache->nextXid = max_xid;
		TransactionIdAdvance(ShmemVariableCache->nextXid);
		LWLockRelease(XidGenLock);
	}

	Assert(!!(parsed->xinfo & XACT_XINFO_HAS_ORIGIN) == (origin_id != InvalidRepOriginId));

	if (parsed->xinfo & XACT_XINFO_HAS_ORIGIN)
		commit_time = parsed->origin_timestamp;
	else
		commit_time = parsed->xact_time;


	TransactionTreeSetCommitTsData(xid, parsed->nsubxacts, parsed->subxacts,
								   commit_time, origin_id,
								   true, false);

	if (standbyState == STANDBY_DISABLED)
	{


		TransactionIdCommitTree(xid, parsed->nsubxacts, parsed->subxacts);
	}
	else
	{


		RecordKnownAssignedTransactionIds(max_xid);


		TransactionIdAsyncCommitTree(
							  xid, parsed->nsubxacts, parsed->subxacts, lsn);


		ExpireTreeKnownAssignedTransactionIds(
						  xid, parsed->nsubxacts, parsed->subxacts, max_xid);


		ProcessCommittedInvalidationMessages(
											 parsed->msgs, parsed->nmsgs,
						  XactCompletionRelcacheInitFileInval(parsed->xinfo),
											 parsed->dbId, parsed->tsId);


		StandbyReleaseLockTree(xid, 0, NULL);
	}

	if (parsed->xinfo & XACT_XINFO_HAS_ORIGIN)
	{

		replorigin_advance(origin_id, parsed->origin_lsn, lsn,
						   false  , false  );
	}


	if (parsed->nrels > 0)
	{


		XLogFlush(lsn);

		for (i = 0; i < parsed->nrels; i++)
		{
			SMgrRelation srel = smgropen(parsed->xnodes[i], InvalidBackendId);
			ForkNumber	fork;

			for (fork = 0; fork <= MAX_FORKNUM; fork++)
				XLogDropRelation(parsed->xnodes[i], fork);
			smgrdounlink(srel, true);
			smgrclose(srel);
		}
	}


	if (XactCompletionForceSyncCommit(parsed->xinfo))
		XLogFlush(lsn);

}
