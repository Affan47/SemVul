simple_heap_delete(Relation relation, ItemPointer tid)
{
	HTSU_Result result;
	ItemPointerData update_ctid;
	TransactionId update_xmax;

	result = heap_delete(relation, tid,
						 &update_ctid, &update_xmax,
						 GetCurrentCommandId(true), InvalidSnapshot,
						 true  );
	switch (result)
	{
		case HeapTupleSelfUpdated:

			elog(ERROR, "tuple already updated by self");
			break;

		case HeapTupleMayBeUpdated:

			break;

		case HeapTupleUpdated:
			elog(ERROR, "tuple concurrently updated");
			break;

		default:
			elog(ERROR, "unrecognized heap_delete status: %u", result);
			break;
	}
}
