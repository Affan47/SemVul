processPendingPage(BuildAccumulator *accum, KeyArray *ka,
				   Page page, OffsetNumber startoff)
{
	ItemPointerData heapptr;
	OffsetNumber i,
				maxoff;
	OffsetNumber attrnum;


	ka->nvalues = 0;

	maxoff = PageGetMaxOffsetNumber(page);
	Assert(maxoff >= FirstOffsetNumber);
	ItemPointerSetInvalid(&heapptr);
	attrnum = 0;

	for (i = startoff; i <= maxoff; i = OffsetNumberNext(i))
	{
		IndexTuple	itup = (IndexTuple) PageGetItem(page, PageGetItemId(page, i));
		OffsetNumber curattnum;
		Datum		curkey;
		GinNullCategory curcategory;


		curattnum = gintuple_get_attrnum(accum->ginstate, itup);

		if (!ItemPointerIsValid(&heapptr))
		{
			heapptr = itup->t_tid;
			attrnum = curattnum;
		}
		else if (!(ItemPointerEquals(&heapptr, &itup->t_tid) &&
				   curattnum == attrnum))
		{


			ginInsertBAEntries(accum, &heapptr, attrnum,
							   ka->keys, ka->categories, ka->nvalues);
			ka->nvalues = 0;
			heapptr = itup->t_tid;
			attrnum = curattnum;
		}


		curkey = gintuple_get_key(accum->ginstate, itup, &curcategory);
		addDatum(ka, curkey, curcategory);
	}


	ginInsertBAEntries(accum, &heapptr, attrnum,
					   ka->keys, ka->categories, ka->nvalues);
}
