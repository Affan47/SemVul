alloc_data_block(struct inode *inode, struct page *page)
{
	struct logfs_block *block;
	u64 bix;
	level_t level;

	if (PagePrivate(page))
		return;

	logfs_unpack_index(page->index, &bix, &level);
	block = __alloc_block(inode->i_sb, inode->i_ino, bix, level);
	block->page = page;

	SetPagePrivate(page);
	page_cache_get(page);
	set_page_private(page, (unsigned long) block);

	block->ops = &indirect_block_ops;
}
