AllocSetStats(MemoryContext context, int level, bool print,
			  MemoryContextCounters *totals)
{
	AllocSet	set = (AllocSet) context;
	Size		nblocks = 0;
	Size		freechunks = 0;
	Size		totalspace = 0;
	Size		freespace = 0;
	AllocBlock	block;
	int			fidx;

	for (block = set->blocks; block != NULL; block = block->next)
	{
		nblocks++;
		totalspace += block->endptr - ((char *) block);
		freespace += block->endptr - block->freeptr;
	}
	for (fidx = 0; fidx < ALLOCSET_NUM_FREELISTS; fidx++)
	{
		AllocChunk	chunk;

		for (chunk = set->freelist[fidx]; chunk != NULL;
			 chunk = (AllocChunk) chunk->aset)
		{
			freechunks++;
			freespace += chunk->size + ALLOC_CHUNKHDRSZ;
		}
	}

	if (print)
	{
		int			i;

		for (i = 0; i < level; i++)
			fprintf(stderr, "  ");
		fprintf(stderr,
			"%s: %zu total in %zd blocks; %zu free (%zd chunks); %zu used\n",
				set->header.name, totalspace, nblocks, freespace, freechunks,
				totalspace - freespace);
	}

	if (totals)
	{
		totals->nblocks += nblocks;
		totals->freechunks += freechunks;
		totals->totalspace += totalspace;
		totals->freespace += freespace;
	}
}
