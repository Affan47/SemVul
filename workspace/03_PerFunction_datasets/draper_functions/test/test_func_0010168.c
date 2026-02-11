AllocSetReset(MemoryContext context)
{
	AllocSet	set = (AllocSet) context;
	AllocBlock	block;

	AssertArg(AllocSetIsValid(set));


	if (set->isReset)
		return;

#ifdef MEMORY_CONTEXT_CHECKING

	AllocSetCheck(context);
#endif


	MemSetAligned(set->freelist, 0, sizeof(set->freelist));

	block = set->blocks;


	set->blocks = set->keeper;

	while (block != NULL)
	{
		AllocBlock	next = block->next;

		if (block == set->keeper)
		{

			char	   *datastart = ((char *) block) + ALLOC_BLOCKHDRSZ;

#ifdef CLOBBER_FREED_MEMORY

			memset(datastart, 0x7F, block->freeptr - datastart);
#endif
			block->freeptr = datastart;
			block->next = NULL;
		}
		else
		{

#ifdef CLOBBER_FREED_MEMORY

			memset(block, 0x7F, block->freeptr - ((char *) block));
#endif
			free(block);
		}
		block = next;
	}


	set->nextBlockSize = set->initBlockSize;

	set->isReset = true;
}
