ocfs2_validate_and_adjust_move_goal(struct inode *inode,
					       struct ocfs2_move_extents *range)
{
	int ret, goal_bit = 0;

	struct buffer_head *gd_bh = NULL;
	struct ocfs2_group_desc *bg;
	struct ocfs2_super *osb = OCFS2_SB(inode->i_sb);
	int c_to_b = 1 << (osb->s_clustersize_bits -
					inode->i_sb->s_blocksize_bits);


	range->me_goal = ocfs2_block_to_cluster_start(inode->i_sb,
						      range->me_goal);


	ret = ocfs2_find_victim_alloc_group(inode, range->me_goal,
					    GLOBAL_BITMAP_SYSTEM_INODE,
					    OCFS2_INVALID_SLOT,
					    &goal_bit, &gd_bh);
	if (ret)
		goto out;

	bg = (struct ocfs2_group_desc *)gd_bh->b_data;


	if (range->me_goal == le64_to_cpu(bg->bg_blkno))
		range->me_goal += c_to_b;


	if ((le16_to_cpu(bg->bg_bits) - goal_bit) * osb->s_clustersize <
								range->me_len) {
		ret = -EINVAL;
		goto out;
	}


	mlog(0, "extents get ready to be moved to #%llu block\n",
	     range->me_goal);

out:
	brelse(gd_bh);

	return ret;
}
