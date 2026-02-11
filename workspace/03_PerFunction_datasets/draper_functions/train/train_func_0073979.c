ginAllocEntryAccumulator(void *arg)
{
	BuildAccumulator *accum = (BuildAccumulator *) arg;
	GinEntryAccumulator *ea;


	if (accum->entryallocator == NULL || accum->eas_used >= DEF_NENTRY)
	{
		accum->entryallocator = palloc(sizeof(GinEntryAccumulator) * DEF_NENTRY);
		accum->allocatedMemory += GetMemoryChunkSpace(accum->entryallocator);
		accum->eas_used = 0;
	}


	ea = accum->entryallocator + accum->eas_used;
	accum->eas_used++;

	return (RBNode *) ea;
}
