CommitTransaction(void)
{
	TransactionState s = CurrentTransactionState;
	TransactionId latestXid;

	ShowTransactionState("CommitTransaction");


	if (s->state != TRANS_INPROGRESS)
		elog(WARNING, "CommitTransaction while in %s state",
			 TransStateAsString(s->state));
	Assert(s->parent == NULL);


	for (;;)
	{


		AfterTriggerFireDeferred();


		if (!PreCommit_Portals(false))
			break;
	}


	AfterTriggerEndXact(true);


	PreCommit_on_commit_actions();


	AtEOXact_LargeObject(true);


	PreCommit_CheckForSerializationFailure();


	PreCommit_Notify();


	HOLD_INTERRUPTS();


	AtEOXact_RelationMap(true);


	s->state = TRANS_COMMIT;


	latestXid = RecordTransactionCommit();

	TRACE_POSTGRESQL_TRANSACTION_COMMIT(MyProc->lxid);


	ProcArrayEndTransaction(MyProc, latestXid);


	CallXactCallbacks(XACT_EVENT_COMMIT);

	ResourceOwnerRelease(TopTransactionResourceOwner,
						 RESOURCE_RELEASE_BEFORE_LOCKS,
						 true, true);


	AtEOXact_Buffers(true);


	AtEOXact_RelationCache(true);


	AtEarlyCommit_Snapshot();


	AtEOXact_Inval(true);


	smgrDoPendingDeletes(true);

	AtEOXact_MultiXact();

	ResourceOwnerRelease(TopTransactionResourceOwner,
						 RESOURCE_RELEASE_LOCKS,
						 true, true);
	ResourceOwnerRelease(TopTransactionResourceOwner,
						 RESOURCE_RELEASE_AFTER_LOCKS,
						 true, true);


	AtEOXact_CatCache(true);

	AtCommit_Notify();
	AtEOXact_GUC(true, 1);
	AtEOXact_SPI(true);
	AtEOXact_on_commit_actions(true);
	AtEOXact_Namespace(true);

	AtEOXact_Files();
	AtEOXact_ComboCid();
	AtEOXact_HashTables(true);
	AtEOXact_PgStat(true);
	AtEOXact_Snapshot(true);
	pgstat_report_xact_timestamp(0);

	CurrentResourceOwner = NULL;
	ResourceOwnerDelete(TopTransactionResourceOwner);
	s->curTransactionOwner = NULL;
	CurTransactionResourceOwner = NULL;
	TopTransactionResourceOwner = NULL;

	AtCommit_Memory();

	s->transactionId = InvalidTransactionId;
	s->subTransactionId = InvalidSubTransactionId;
	s->nestingLevel = 0;
	s->gucNestLevel = 0;
	s->childXids = NULL;
	s->nChildXids = 0;
	s->maxChildXids = 0;


	s->state = TRANS_DEFAULT;

	RESUME_INTERRUPTS();
}
