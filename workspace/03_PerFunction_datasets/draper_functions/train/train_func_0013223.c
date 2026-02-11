smgrcreate(SMgrRelation reln, bool isTemp, bool isRedo)
{
	XLogRecPtr	lsn;
	XLogRecData rdata;
	xl_smgr_create xlrec;
	PendingRelDelete *pending;


	TablespaceCreateDbspace(reln->smgr_rnode.spcNode,
							reln->smgr_rnode.dbNode,
							isRedo);

	(*(smgrsw[reln->smgr_which].smgr_create)) (reln, isRedo);

	if (isRedo)
		return;


	xlrec.rnode = reln->smgr_rnode;

	rdata.data = (char *) &xlrec;
	rdata.len = sizeof(xlrec);
	rdata.buffer = InvalidBuffer;
	rdata.next = NULL;

	lsn = XLogInsert(RM_SMGR_ID, XLOG_SMGR_CREATE, &rdata);


	pending = (PendingRelDelete *)
		MemoryContextAlloc(TopMemoryContext, sizeof(PendingRelDelete));
	pending->relnode = reln->smgr_rnode;
	pending->which = reln->smgr_which;
	pending->isTemp = isTemp;
	pending->atCommit = false;
	pending->nestLevel = GetCurrentTransactionNestLevel();
	pending->next = pendingDeletes;
	pendingDeletes = pending;
}
