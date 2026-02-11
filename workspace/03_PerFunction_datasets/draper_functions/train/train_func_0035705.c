comparetup_index_btree(const SortTuple *a, const SortTuple *b,
					   Tuplesortstate *state)
{


	ScanKey		scanKey = state->indexScanKey;
	IndexTuple	tuple1;
	IndexTuple	tuple2;
	int			keysz;
	TupleDesc	tupDes;
	bool		equal_hasnull = false;
	int			nkey;
	int32		compare;


	CHECK_FOR_INTERRUPTS();


	compare = inlineApplySortFunction(&scanKey->sk_func, scanKey->sk_flags,
									  a->datum1, a->isnull1,
									  b->datum1, b->isnull1);
	if (compare != 0)
		return compare;


	if (a->isnull1)
		equal_hasnull = true;


	tuple1 = (IndexTuple) a->tuple;
	tuple2 = (IndexTuple) b->tuple;
	keysz = state->nKeys;
	tupDes = RelationGetDescr(state->indexRel);
	scanKey++;
	for (nkey = 2; nkey <= keysz; nkey++, scanKey++)
	{
		Datum		datum1,
					datum2;
		bool		isnull1,
					isnull2;

		datum1 = index_getattr(tuple1, nkey, tupDes, &isnull1);
		datum2 = index_getattr(tuple2, nkey, tupDes, &isnull2);

		compare = inlineApplySortFunction(&scanKey->sk_func, scanKey->sk_flags,
										  datum1, isnull1,
										  datum2, isnull2);
		if (compare != 0)
			return compare;


		if (isnull1)
			equal_hasnull = true;
	}


	if (state->enforceUnique && !equal_hasnull && tuple1 != tuple2)
		ereport(ERROR,
				(errcode(ERRCODE_UNIQUE_VIOLATION),
				 errmsg("could not create unique index \"%s\"",
						RelationGetRelationName(state->indexRel)),
				 errdetail("Table contains duplicated values.")));


	{
		BlockNumber blk1 = ItemPointerGetBlockNumber(&tuple1->t_tid);
		BlockNumber blk2 = ItemPointerGetBlockNumber(&tuple2->t_tid);

		if (blk1 != blk2)
			return (blk1 < blk2) ? -1 : 1;
	}
	{
		OffsetNumber pos1 = ItemPointerGetOffsetNumber(&tuple1->t_tid);
		OffsetNumber pos2 = ItemPointerGetOffsetNumber(&tuple2->t_tid);

		if (pos1 != pos2)
			return (pos1 < pos2) ? -1 : 1;
	}

	return 0;
}
