ocfs2_get_reflink_xattr_value_root(struct super_block *sb,
					struct buffer_head *bh,
					struct ocfs2_xattr_header *xh,
					int offset,
					struct ocfs2_xattr_value_root **xv,
					struct buffer_head **ret_bh,
					void *para)
{
	struct ocfs2_reflink_xattr_tree_args *args =
			(struct ocfs2_reflink_xattr_tree_args *)para;
	struct ocfs2_xattr_bucket *bucket;

	if (bh == args->old_bucket->bu_bhs[0])
		bucket = args->old_bucket;
	else
		bucket = args->new_bucket;

	return ocfs2_get_xattr_tree_value_root(sb, bucket, offset,
					       xv, ret_bh);
}
