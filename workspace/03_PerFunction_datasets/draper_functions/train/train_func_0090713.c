heap_get_root_tuples(Page page, OffsetNumber *root_offsets)
{
	OffsetNumber offnum,
				maxoff;

	MemSet(root_offsets, 0, MaxHeapTuplesPerPage * sizeof(OffsetNumber));

	maxoff = PageGetMaxOffsetNumber(page);
	for (offnum = FirstOffsetNumber; offnum <= maxoff; offnum++)
	{
		ItemId		lp = PageGetItemId(page, offnum);
		HeapTupleHeader htup;
		OffsetNumber nextoffnum;
		TransactionId priorXmax;


		if (!ItemIdIsUsed(lp) || ItemIdIsDead(lp))
			continue;

		if (ItemIdIsNormal(lp))
		{
			htup = (HeapTupleHeader) PageGetItem(page, lp);


			if (HeapTupleHeaderIsHeapOnly(htup))
				continue;


			root_offsets[offnum - 1] = offnum;


			if (!HeapTupleHeaderIsHotUpdated(htup))
				continue;


			nextoffnum = ItemPointerGetOffsetNumber(&htup->t_ctid);
			priorXmax = HeapTupleHeaderGetXmax(htup);
		}
		else
		{

			Assert(ItemIdIsRedirected(lp));

			nextoffnum = ItemIdGetRedirect(lp);
			priorXmax = InvalidTransactionId;
		}


		for (;;)
		{
			lp = PageGetItemId(page, nextoffnum);


			if (!ItemIdIsNormal(lp))
				break;

			htup = (HeapTupleHeader) PageGetItem(page, lp);

			if (TransactionIdIsValid(priorXmax) &&
				!TransactionIdEquals(priorXmax, HeapTupleHeaderGetXmin(htup)))
				break;


			root_offsets[nextoffnum - 1] = offnum;


			if (!HeapTupleHeaderIsHotUpdated(htup))
				break;

			nextoffnum = ItemPointerGetOffsetNumber(&htup->t_ctid);
			priorXmax = HeapTupleHeaderGetXmax(htup);
		}
	}
}
