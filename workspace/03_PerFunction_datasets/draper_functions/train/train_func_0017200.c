submit_logged_buffer(struct buffer_head *bh)
{
	get_bh(bh);
	bh->b_end_io = reiserfs_end_buffer_io_sync;
	clear_buffer_journal_new(bh);
	clear_buffer_dirty(bh);
	if (!test_clear_buffer_journal_test(bh))
		BUG();
	if (!buffer_uptodate(bh))
		BUG();
	submit_bh(WRITE, bh);
}
