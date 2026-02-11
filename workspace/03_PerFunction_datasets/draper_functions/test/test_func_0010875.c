__nilfs_get_page_block(struct page *page, unsigned long block, pgoff_t index,
		       int blkbits, unsigned long b_state)

{
	unsigned long first_block;
	struct buffer_head *bh;

	if (!page_has_buffers(page))
		create_empty_buffers(page, 1 << blkbits, b_state);

	first_block = (unsigned long)index << (PAGE_CACHE_SHIFT - blkbits);
	bh = nilfs_page_get_nth_block(page, block - first_block);

	touch_buffer(bh);
	wait_on_buffer(bh);
	return bh;
}
