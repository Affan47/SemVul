SetReindexProcessing(Oid heapOid, Oid indexOid)
{
	Assert(OidIsValid(heapOid) && OidIsValid(indexOid));

	if (OidIsValid(currentlyReindexedIndex))
		elog(ERROR, "cannot reindex while reindexing");
	currentlyReindexedHeap = heapOid;
	currentlyReindexedIndex = indexOid;
}
