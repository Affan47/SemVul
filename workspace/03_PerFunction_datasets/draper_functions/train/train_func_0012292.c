submit_ordered_buffer(struct buffer_head *bh)
{
	get_bh(bh);
	bh->b_end_io = reiserfs_end_ordered_io;
	clear_buffer_dirty(bh);
	if (!buffer_uptodate(bh))
		BUG();
	submit_bh(WRITE, bh);
}
