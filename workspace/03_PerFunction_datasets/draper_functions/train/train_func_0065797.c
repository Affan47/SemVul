EAAllocate(BuildAccumulator *accum)
{
	if (accum->entryallocator == NULL || accum->length >= DEF_NENTRY)
	{
		accum->entryallocator = palloc(sizeof(EntryAccumulator) * DEF_NENTRY);
		accum->allocatedMemory += sizeof(EntryAccumulator) * DEF_NENTRY;
		accum->length = 0;
	}

	accum->length++;
	return accum->entryallocator + accum->length - 1;
}
