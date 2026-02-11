ocfs2_double_unlock(struct inode *inode1, struct inode *inode2)
{
	ocfs2_inode_unlock(inode1, 1);

	if (inode1 != inode2)
		ocfs2_inode_unlock(inode2, 1);
}
