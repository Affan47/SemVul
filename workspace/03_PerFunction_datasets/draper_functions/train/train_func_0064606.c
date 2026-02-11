ocfs2_evict_inode(struct inode *inode)
{
	if (!inode->i_nlink ||
	    (OCFS2_I(inode)->ip_flags & OCFS2_INODE_MAYBE_ORPHANED)) {
		ocfs2_delete_inode(inode);
	} else {
		truncate_inode_pages_final(&inode->i_data);
	}
	ocfs2_clear_inode(inode);
}
