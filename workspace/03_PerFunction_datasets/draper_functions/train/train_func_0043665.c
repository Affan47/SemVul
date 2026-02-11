jfs_issue_discard(struct inode *ip, u64 blkno, u64 nblocks)
{
	struct super_block *sb = ip->i_sb;
	int r = 0;

	r = sb_issue_discard(sb, blkno, nblocks, GFP_NOFS, 0);
	if (unlikely(r != 0)) {
		jfs_err("JFS: sb_issue_discard" \
			"(%p, %llu, %llu, GFP_NOFS, 0) = %d => failed!\n",
			sb, (unsigned long long)blkno,
			(unsigned long long)nblocks, r);
	}

	jfs_info("JFS: sb_issue_discard" \
		"(%p, %llu, %llu, GFP_NOFS, 0) = %d\n",
		sb, (unsigned long long)blkno,
		(unsigned long long)nblocks, r);

	return;
}
