omfs_remove(struct inode *dir, struct dentry *dentry)
{
	struct inode *inode = d_inode(dentry);
	int ret;


	if (S_ISDIR(inode->i_mode) &&
	    !omfs_dir_is_empty(inode))
		return -ENOTEMPTY;

	ret = omfs_delete_entry(dentry);
	if (ret)
		return ret;

	clear_nlink(inode);
	mark_inode_dirty(inode);
	mark_inode_dirty(dir);
	return 0;
}
