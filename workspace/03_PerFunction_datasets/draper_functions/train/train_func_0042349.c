GinFormTuple(Relation index, GinState *ginstate,
			 OffsetNumber attnum, Datum key,
			 ItemPointerData *ipd, uint32 nipd, bool errorTooBig)
{
	bool		isnull[2] = {FALSE, FALSE};
	IndexTuple	itup;
	uint32		newsize;

	if (ginstate->oneCol)
		itup = index_form_tuple(ginstate->origTupdesc, &key, isnull);
	else
	{
		Datum		datums[2];

		datums[0] = UInt16GetDatum(attnum);
		datums[1] = key;
		itup = index_form_tuple(ginstate->tupdesc[attnum - 1], datums, isnull);
	}

	GinSetOrigSizePosting(itup, IndexTupleSize(itup));

	if (nipd > 0)
	{
		newsize = MAXALIGN(SHORTALIGN(IndexTupleSize(itup)) + sizeof(ItemPointerData) * nipd);
		if (newsize > Min(INDEX_SIZE_MASK, GinMaxItemSize))
		{
			if (errorTooBig)
				ereport(ERROR,
						(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
						 errmsg("index row size %lu exceeds maximum %lu for index \"%s\"",
								(unsigned long) newsize,
								(unsigned long) Min(INDEX_SIZE_MASK,
													GinMaxItemSize),
								RelationGetRelationName(index))));
			return NULL;
		}

		itup = repalloc(itup, newsize);


		itup->t_info &= ~INDEX_SIZE_MASK;
		itup->t_info |= newsize;

		if (ipd)
			memcpy(GinGetPosting(itup), ipd, sizeof(ItemPointerData) * nipd);
		GinSetNPosting(itup, nipd);
	}
	else
	{


		newsize = MAXALIGN(SHORTALIGN(IndexTupleSize(itup)) + sizeof(ItemPointerData));
		if (newsize > Min(INDEX_SIZE_MASK, GinMaxItemSize))
		{
			if (errorTooBig)
				ereport(ERROR,
						(errcode(ERRCODE_PROGRAM_LIMIT_EXCEEDED),
						 errmsg("index row size %lu exceeds maximum %lu for index \"%s\"",
								(unsigned long) newsize,
								(unsigned long) Min(INDEX_SIZE_MASK,
													GinMaxItemSize),
								RelationGetRelationName(index))));
			return NULL;
		}

		GinSetNPosting(itup, 0);
	}
	return itup;
}
