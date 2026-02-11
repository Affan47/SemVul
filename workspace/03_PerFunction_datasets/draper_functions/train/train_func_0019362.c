gfs2_end_log_write_bh(struct gfs2_sbd *sdp, struct bio_vec *bvec,
				  int error)
{
	struct buffer_head *bh, *next;
	struct page *page = bvec->bv_page;
	unsigned size;

	bh = page_buffers(page);
	size = bvec->bv_len;
	while (bh_offset(bh) < bvec->bv_offset)
		bh = bh->b_this_page;
	do {
		if (error)
			set_buffer_write_io_error(bh);
		unlock_buffer(bh);
		next = bh->b_this_page;
		size -= bh->b_size;
		brelse(bh);
		bh = next;
	} while(bh && size);
}
