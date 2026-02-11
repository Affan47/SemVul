ocfs2_lock_xattr_remove_allocators(struct inode *inode,
					struct ocfs2_xattr_value_root *xv,
					struct ocfs2_caching_info *ref_ci,
					struct buffer_head *ref_root_bh,
					struct ocfs2_alloc_context **meta_ac,
					int *ref_credits)
{
	int ret, meta_add = 0;
	u32 p_cluster, num_clusters;
	unsigned int ext_flags;

	*ref_credits = 0;
	ret = ocfs2_xattr_get_clusters(inode, 0, &p_cluster,
				       &num_clusters,
				       &xv->xr_list,
				       &ext_flags);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	if (!(ext_flags & OCFS2_EXT_REFCOUNTED))
		goto out;

	ret = ocfs2_refcounted_xattr_delete_need(inode, ref_ci,
						 ref_root_bh, xv,
						 &meta_add, ref_credits);
	if (ret) {
		mlog_errno(ret);
		goto out;
	}

	ret = ocfs2_reserve_new_metadata_blocks(OCFS2_SB(inode->i_sb),
						meta_add, meta_ac);
	if (ret)
		mlog_errno(ret);

out:
	return ret;
}
