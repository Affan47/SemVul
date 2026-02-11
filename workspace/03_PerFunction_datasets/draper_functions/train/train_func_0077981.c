extent_invalidatepage(struct extent_io_tree *tree,
			  struct page *page, unsigned long offset)
{
	struct extent_state *cached_state = NULL;
	u64 start = page_offset(page);
	u64 end = start + PAGE_CACHE_SIZE - 1;
	size_t blocksize = page->mapping->host->i_sb->s_blocksize;

	start += ALIGN(offset, blocksize);
	if (start > end)
		return 0;

	lock_extent_bits(tree, start, end, 0, &cached_state);
	wait_on_page_writeback(page);
	clear_extent_bit(tree, start, end,
			 EXTENT_LOCKED | EXTENT_DIRTY | EXTENT_DELALLOC |
			 EXTENT_DO_ACCOUNTING,
			 1, 1, &cached_state, GFP_NOFS);
	return 0;
}
