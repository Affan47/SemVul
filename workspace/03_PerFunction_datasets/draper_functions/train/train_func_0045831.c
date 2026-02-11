gfs2_quota_change_out(struct gfs2_quota_change *qc,
			   struct gfs2_buffer_head *bh)
{
	struct gfs2_quota_change *str = (struct gfs2_quota_change *)(bh->b_data +
		sizeof(struct gfs2_meta_header));

	CPOUT_64(qc, str, qc_change);
	CPOUT_32(qc, str, qc_flags);
	CPOUT_32(qc, str, qc_id);
	bmodified(bh);
}
