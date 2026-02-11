ocfs2_validate_quota_block(struct super_block *sb, struct buffer_head *bh)
{
	struct ocfs2_disk_dqtrailer *dqt =
		ocfs2_block_dqtrailer(sb->s_blocksize, bh->b_data);

	trace_ocfs2_validate_quota_block((unsigned long long)bh->b_blocknr);

	BUG_ON(!buffer_uptodate(bh));


	return ocfs2_validate_meta_ecc(sb, bh->b_data, &dqt->dq_check);
}
