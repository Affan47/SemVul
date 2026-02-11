btbeginscan(PG_FUNCTION_ARGS)
{
	Relation	rel = (Relation) PG_GETARG_POINTER(0);
	int			nkeys = PG_GETARG_INT32(1);
	int			norderbys = PG_GETARG_INT32(2);
	IndexScanDesc scan;
	BTScanOpaque so;


	Assert(norderbys == 0);


	scan = RelationGetIndexScan(rel, nkeys, norderbys);


	so = (BTScanOpaque) palloc(sizeof(BTScanOpaqueData));
	so->currPos.buf = so->markPos.buf = InvalidBuffer;
	if (scan->numberOfKeys > 0)
		so->keyData = (ScanKey) palloc(scan->numberOfKeys * sizeof(ScanKeyData));
	else
		so->keyData = NULL;
	so->killedItems = NULL;
	so->numKilled = 0;
	scan->opaque = so;

	PG_RETURN_POINTER(scan);
}
