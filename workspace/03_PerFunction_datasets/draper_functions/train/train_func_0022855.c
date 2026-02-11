nilfs_forget_buffer(struct buffer_head *bh)
{
	struct page *page = bh->b_page;
	const unsigned long clear_bits =
		(1 << BH_Uptodate | 1 << BH_Dirty | 1 << BH_Mapped |
		 1 << BH_Async_Write | 1 << BH_NILFS_Volatile |
		 1 << BH_NILFS_Checked | 1 << BH_NILFS_Redirected);

	lock_buffer(bh);
	set_mask_bits(&bh->b_state, clear_bits, 0);
	if (nilfs_page_buffers_clean(page))
		__nilfs_clear_page_dirty(page);

	bh->b_blocknr = -1;
	ClearPageUptodate(page);
	ClearPageMappedToDisk(page);
	unlock_buffer(bh);
	brelse(bh);
}
