simple_heap_update(Relation relation, ItemPointer otid, HeapTuple tup)
{
	HTSU_Result result;
	ItemPointerData update_ctid;
	TransactionId update_xmax;

	result = heap_update(relation, otid, tup,
						 &update_ctid, &update_xmax,
						 GetCurrentCommandId(), InvalidSnapshot,
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
			elog(ERROR, "unrecognized heap_update status: %u", result);
			break;
	}
}
