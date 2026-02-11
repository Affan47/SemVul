zipinfo_memory_allocated (void)
{
	int i;
	index_t accum_blocks = 0;
	for (i = 0; i < MAX_EGKEYS; i++) {
		if (Zipinfo[i].blockindex != NULL) {
		 	accum_blocks += Zipinfo[i].totalblocks;
		}
	}
	return (size_t)accum_blocks * sizeof(index_t);
}
