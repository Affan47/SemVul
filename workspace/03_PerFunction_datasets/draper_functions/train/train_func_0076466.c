_hash_binsearch_last(Page page, uint32 hash_value)
{
	OffsetNumber upper;
	OffsetNumber lower;


	upper = PageGetMaxOffsetNumber(page);
	lower = FirstOffsetNumber - 1;

	while (upper > lower)
	{
		IndexTuple	itup;
		OffsetNumber off;
		uint32		hashkey;

		off = (upper + lower + 1) / 2;
		Assert(OffsetNumberIsValid(off));

		itup = (IndexTuple) PageGetItem(page, PageGetItemId(page, off));
		hashkey = _hash_get_indextuple_hashkey(itup);
		if (hashkey > hash_value)
			upper = off - 1;
		else
			lower = off;
	}

	return lower;
}
