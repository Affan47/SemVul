SyncRepWaitForLSN(XLogRecPtr XactCommitLSN)
{
	char	   *new_status = NULL;
	const char *old_status;


	if (!SyncRepRequested() || !SyncStandbysDefined())
		return;

	Assert(SHMQueueIsDetached(&(MyProc->syncRepLinks)));
	Assert(WalSndCtl != NULL);

	LWLockAcquire(SyncRepLock, LW_EXCLUSIVE);
	Assert(MyProc->syncRepState == SYNC_REP_NOT_WAITING);


	if (!WalSndCtl->sync_standbys_defined ||
		XLByteLE(XactCommitLSN, WalSndCtl->lsn))
	{
		LWLockRelease(SyncRepLock);
		return;
	}


	MyProc->waitLSN = XactCommitLSN;
	MyProc->syncRepState = SYNC_REP_WAITING;
	SyncRepQueueInsert();
	Assert(SyncRepQueueIsOrderedByLSN());
	LWLockRelease(SyncRepLock);


	if (update_process_title)
	{
		int			len;

		old_status = get_ps_display(&len);
		new_status = (char *) palloc(len + 32 + 1);
		memcpy(new_status, old_status, len);
		sprintf(new_status + len, " waiting for %X/%X",
				XactCommitLSN.xlogid, XactCommitLSN.xrecoff);
		set_ps_display(new_status, false);
		new_status[len] = '\0';
	}


	for (;;)
	{
		int			syncRepState;


		ResetLatch(&MyProc->procLatch);


		syncRepState = MyProc->syncRepState;
		if (syncRepState == SYNC_REP_WAITING)
		{
			LWLockAcquire(SyncRepLock, LW_SHARED);
			syncRepState = MyProc->syncRepState;
			LWLockRelease(SyncRepLock);
		}
		if (syncRepState == SYNC_REP_WAIT_COMPLETE)
			break;


		if (ProcDiePending)
		{
			ereport(WARNING,
					(errcode(ERRCODE_ADMIN_SHUTDOWN),
					 errmsg("canceling the wait for synchronous replication and terminating connection due to administrator command"),
					 errdetail("The transaction has already committed locally, but might not have been replicated to the standby.")));
			whereToSendOutput = DestNone;
			SyncRepCancelWait();
			break;
		}


		if (QueryCancelPending)
		{
			QueryCancelPending = false;
			ereport(WARNING,
					(errmsg("canceling wait for synchronous replication due to user request"),
					 errdetail("The transaction has already committed locally, but might not have been replicated to the standby.")));
			SyncRepCancelWait();
			break;
		}


		if (!PostmasterIsAlive(true))
		{
			ProcDiePending = true;
			whereToSendOutput = DestNone;
			SyncRepCancelWait();
			break;
		}


		WaitLatch(&MyProc->procLatch, 10000L);
	}


	Assert(SHMQueueIsDetached(&(MyProc->syncRepLinks)));
	MyProc->syncRepState = SYNC_REP_NOT_WAITING;
	MyProc->waitLSN.xlogid = 0;
	MyProc->waitLSN.xrecoff = 0;

	if (new_status)
	{

		set_ps_display(new_status, false);
		pfree(new_status);
	}
}
