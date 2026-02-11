ocfs2_verify_group_and_input(struct inode *inode,
					struct ocfs2_dinode *di,
					struct ocfs2_new_group_input *input,
					struct buffer_head *group_bh)
{
	u16 cl_count = le16_to_cpu(di->id2.i_chain.cl_count);
	u16 cl_cpg = le16_to_cpu(di->id2.i_chain.cl_cpg);
	u16 next_free = le16_to_cpu(di->id2.i_chain.cl_next_free_rec);
	u32 cluster = ocfs2_blocks_to_clusters(inode->i_sb, input->group);
	u32 total_clusters = le32_to_cpu(di->i_clusters);
	int ret = -EINVAL;

	if (cluster < total_clusters)
		mlog(ML_ERROR, "add a group which is in the current volume.\n");
	else if (input->chain >= cl_count)
		mlog(ML_ERROR, "input chain exceeds the limit.\n");
	else if (next_free != cl_count && next_free != input->chain)
		mlog(ML_ERROR,
		     "the add group should be in chain %u\n", next_free);
	else if (total_clusters + input->clusters < total_clusters)
		mlog(ML_ERROR, "add group's clusters overflow.\n");
	else if (input->clusters > cl_cpg)
		mlog(ML_ERROR, "the cluster exceeds the maximum of a group\n");
	else if (input->frees > input->clusters)
		mlog(ML_ERROR, "the free cluster exceeds the total clusters\n");
	else if (total_clusters % cl_cpg != 0)
		mlog(ML_ERROR,
		     "the last group isn't full. Use group extend first.\n");
	else if (input->group != ocfs2_which_cluster_group(inode, cluster))
		mlog(ML_ERROR, "group blkno is invalid\n");
	else if ((ret = ocfs2_check_new_group(inode, di, input, group_bh)))
		mlog(ML_ERROR, "group descriptor check failed.\n");
	else
		ret = 0;

	return ret;
}
