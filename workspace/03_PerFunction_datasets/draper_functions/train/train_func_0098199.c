initialize_block_counters(struct page *page, struct logfs_block *block,
		__be64 *array, int page_is_empty)
{
	u64 ptr;
	int i, start;

	block->partial = 0;
	block->full = 0;
	start = 0;
	if (page->index < first_indirect_block()) {

		return;
	}
	if (page->index == first_indirect_block()) {

		start = I0_BLOCKS;
		block->full = I0_BLOCKS;
	}
	if (!page_is_empty) {
		for (i = start; i < LOGFS_BLOCK_FACTOR; i++) {
			ptr = be64_to_cpu(array[i]);
			if (ptr)
				block->partial++;
			if (ptr & LOGFS_FULLY_POPULATED)
				block->full++;
		}
	}
}
