heap_page_prune_opt(Relation relation, Buffer buffer)
{
	Page		page = BufferGetPage(buffer);
	Size		minfree;
	TransactionId OldestXmin;


	if (RecoveryInProgress())
		return;


	if (IsCatalogRelation(relation) ||
		RelationIsAccessibleInLogicalDecoding(relation))
		OldestXmin = RecentGlobalXmin;
	else
		OldestXmin = RecentGlobalDataXmin;

	Assert(TransactionIdIsValid(OldestXmin));


	if (!PageIsPrunable(page, OldestXmin))
		return;


	minfree = RelationGetTargetPageFreeSpace(relation,
											 HEAP_DEFAULT_FILLFACTOR);
	minfree = Max(minfree, BLCKSZ / 10);

	if (PageIsFull(page) || PageGetHeapFreeSpace(page) < minfree)
	{

		if (!ConditionalLockBufferForCleanup(buffer))
			return;


		if (PageIsFull(page) || PageGetHeapFreeSpace(page) < minfree)
		{
			TransactionId ignore = InvalidTransactionId;


			(void) heap_page_prune(relation, buffer, OldestXmin, true, &ignore);
		}


		LockBuffer(buffer, BUFFER_LOCK_UNLOCK);
	}
}
