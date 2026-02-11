RelationGetIndexScan(Relation indexRelation,
					 int nkeys, ScanKey key)
{
	IndexScanDesc scan;

	scan = (IndexScanDesc) palloc(sizeof(IndexScanDescData));

	scan->heapRelation = NULL;
	scan->indexRelation = indexRelation;
	scan->xs_snapshot = SnapshotNow;
	scan->numberOfKeys = nkeys;


	if (nkeys > 0)
		scan->keyData = (ScanKey) palloc(sizeof(ScanKeyData) * nkeys);
	else
		scan->keyData = NULL;

	scan->is_multiscan = false;
	scan->kill_prior_tuple = false;
	scan->ignore_killed_tuples = true;

	scan->opaque = NULL;

	ItemPointerSetInvalid(&scan->currentItemData);
	ItemPointerSetInvalid(&scan->currentMarkData);

	ItemPointerSetInvalid(&scan->xs_ctup.t_self);
	scan->xs_ctup.t_data = NULL;
	scan->xs_cbuf = InvalidBuffer;

	pgstat_initstats(&scan->xs_pgstat_info, indexRelation);


	index_rescan(scan, key);

	return scan;
}
