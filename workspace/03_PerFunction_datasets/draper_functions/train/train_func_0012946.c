end_buffer_write_sync(struct buffer_head *bh, int uptodate)
{
	if (uptodate) {
		set_buffer_uptodate(bh);
	} else {
		buffer_io_error(bh, ", lost sync page write");
		set_buffer_write_io_error(bh);
		clear_buffer_uptodate(bh);
	}
	unlock_buffer(bh);
	put_bh(bh);
}
