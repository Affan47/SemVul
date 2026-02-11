gfs2_log_header_out(struct gfs2_log_header *lh,
			 struct gfs2_buffer_head *bh)
{
	struct gfs2_log_header *str = (struct gfs2_log_header *)bh->b_data;

	gfs2_meta_header_out_bh(&lh->lh_header, bh);
	CPOUT_64(lh, str, lh_sequence);
	CPOUT_32(lh, str, lh_flags);
	CPOUT_32(lh, str, lh_tail);
	CPOUT_32(lh, str, lh_blkno);
	CPOUT_32(lh, str, lh_hash);
	bmodified(bh);
}
