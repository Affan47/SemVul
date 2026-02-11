ocfs2_fill_new_dir(struct ocfs2_super *osb,
		       handle_t *handle,
		       struct inode *parent,
		       struct inode *inode,
		       struct buffer_head *fe_bh,
		       struct ocfs2_alloc_context *data_ac,
		       struct ocfs2_alloc_context *meta_ac)

{
	BUG_ON(!ocfs2_supports_inline_data(osb) && data_ac == NULL);

	if (OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL)
		return ocfs2_fill_new_dir_id(osb, handle, parent, inode, fe_bh);

	if (ocfs2_supports_indexed_dirs(osb))
		return ocfs2_fill_new_dir_dx(osb, handle, parent, inode, fe_bh,
					     data_ac, meta_ac);

	return ocfs2_fill_new_dir_el(osb, handle, parent, inode, fe_bh,
				     data_ac, NULL);
}
