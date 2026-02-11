TransactionTreeSetCommitTsData(TransactionId xid, int nsubxids,
							   TransactionId *subxids, TimestampTz timestamp,
							   RepOriginId nodeid,
							   bool replaying_xlog, bool write_xlog)
{
	int			i;
	TransactionId headxid;
	TransactionId newestXact;


	Assert(!(write_xlog && replaying_xlog));


	if (!track_commit_timestamp && !replaying_xlog)
		return;


	if (write_xlog)
		WriteSetTimestampXlogRec(xid, nsubxids, subxids, timestamp, nodeid);


	if (nsubxids > 0)
		newestXact = subxids[nsubxids - 1];
	else
		newestXact = xid;


	for (i = 0, headxid = xid;;)
	{
		int			pageno = TransactionIdToCTsPage(headxid);
		int			j;

		for (j = i; j < nsubxids; j++)
		{
			if (TransactionIdToCTsPage(subxids[j]) != pageno)
				break;
		}


		SetXidCommitTsInPage(headxid, j - i, subxids + i, timestamp, nodeid,
							 pageno);


		if (j + 1 >= nsubxids)
			break;


		headxid = subxids[j];
		i += j - i + 1;
	}


	LWLockAcquire(CommitTsLock, LW_EXCLUSIVE);
	commitTsShared->xidLastCommit = xid;
	commitTsShared->dataLastCommit.time = timestamp;
	commitTsShared->dataLastCommit.nodeid = nodeid;


	if (TransactionIdPrecedes(ShmemVariableCache->newestCommitTs, newestXact))
		ShmemVariableCache->newestCommitTs = newestXact;
	LWLockRelease(CommitTsLock);
}
