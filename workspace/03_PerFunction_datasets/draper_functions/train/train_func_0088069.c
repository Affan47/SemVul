nilfs_sufile_set_segment_usage(struct inode *sufile, __u64 segnum,
				   unsigned long nblocks, time_t modtime)
{
	struct buffer_head *bh;
	struct nilfs_segment_usage *su;
	void *kaddr;
	int ret;

	down_write(&NILFS_MDT(sufile)->mi_sem);
	ret = nilfs_sufile_get_segment_usage_block(sufile, segnum, 0, &bh);
	if (ret < 0)
		goto out_sem;

	kaddr = kmap_atomic(bh->b_page);
	su = nilfs_sufile_block_get_segment_usage(sufile, segnum, bh, kaddr);
	WARN_ON(nilfs_segment_usage_error(su));
	if (modtime)
		su->su_lastmod = cpu_to_le64(modtime);
	su->su_nblocks = cpu_to_le32(nblocks);
	kunmap_atomic(kaddr);

	mark_buffer_dirty(bh);
	nilfs_mdt_mark_dirty(sufile);
	brelse(bh);

 out_sem:
	up_write(&NILFS_MDT(sufile)->mi_sem);
	return ret;
}
