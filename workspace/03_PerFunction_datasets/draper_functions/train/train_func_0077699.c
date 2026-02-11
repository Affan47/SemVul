hashgetmulti(PG_FUNCTION_ARGS)
{
	IndexScanDesc scan = (IndexScanDesc) PG_GETARG_POINTER(0);
	ItemPointer tids = (ItemPointer) PG_GETARG_POINTER(1);
	int32		max_tids = PG_GETARG_INT32(2);
	int32	   *returned_tids = (int32 *) PG_GETARG_POINTER(3);
	HashScanOpaque so = (HashScanOpaque) scan->opaque;
	Relation	rel = scan->indexRelation;
	bool		res = true;
	int32		ntids = 0;


	if (BufferIsValid(so->hashso_curbuf))
		_hash_chgbufaccess(rel, so->hashso_curbuf, HASH_NOLOCK, HASH_READ);

	while (ntids < max_tids)
	{


		if (ItemPointerIsValid(&(scan->currentItemData)))
			res = _hash_next(scan, ForwardScanDirection);
		else
			res = _hash_first(scan, ForwardScanDirection);


		if (scan->ignore_killed_tuples)
		{
			while (res)
			{
				Page		page;
				OffsetNumber offnum;

				offnum = ItemPointerGetOffsetNumber(&(scan->currentItemData));
				page = BufferGetPage(so->hashso_curbuf);
				if (!ItemIdDeleted(PageGetItemId(page, offnum)))
					break;
				res = _hash_next(scan, ForwardScanDirection);
			}
		}

		if (!res)
			break;

		tids[ntids] = scan->xs_ctup.t_self;
		ntids++;
	}


	if (BufferIsValid(so->hashso_curbuf))
		_hash_chgbufaccess(rel, so->hashso_curbuf, HASH_READ, HASH_NOLOCK);

	*returned_tids = ntids;
	PG_RETURN_BOOL(res);
}
