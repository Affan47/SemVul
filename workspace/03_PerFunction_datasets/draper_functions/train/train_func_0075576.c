ReindexIsProcessingIndex(Oid indexOid)
{
	return indexOid == currentlyReindexedIndex ||
		list_member_oid(pendingReindexedIndexes, indexOid);
}
