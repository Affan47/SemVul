ocfs2_dx_dir_new_cluster(struct inode *dir,
				    struct ocfs2_extent_tree *et,
				    u32 cpos, handle_t *handle,
				    struct ocfs2_alloc_context *data_ac,
				    struct ocfs2_alloc_context *meta_ac,
				    struct buffer_head **dx_leaves,
				    int num_dx_leaves)
{
	int ret;
	u64 phys_blkno;

	ret = __ocfs2_dx_dir_new_cluster(dir, cpos, handle, data_ac, dx_leaves,
					 num_dx_leaves, &phys_blkno);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_insert_extent(handle, et, cpos, phys_blkno, 1, 0,
				  meta_ac);
	if (ret)
		mlog_errno(ret);
out:
	return ret;
}
