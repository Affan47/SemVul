ginInsertRecordBA(BuildAccumulator *accum, ItemPointer heapptr, OffsetNumber attnum,
				  Datum *entries, int32 nentry)
{
	uint32		step = nentry;

	if (nentry <= 0)
		return;

	Assert(ItemPointerIsValid(heapptr) && attnum >= FirstOffsetNumber);


	step |= (step >> 1);
	step |= (step >> 2);
	step |= (step >> 4);
	step |= (step >> 8);
	step |= (step >> 16);
	step >>= 1;
	step++;

	while (step > 0)
	{
		int			i;

		for (i = step - 1; i < nentry && i >= 0; i += step << 1  )
			ginInsertEntry(accum, heapptr, attnum, entries[i]);

		step >>= 1;
	}
}
