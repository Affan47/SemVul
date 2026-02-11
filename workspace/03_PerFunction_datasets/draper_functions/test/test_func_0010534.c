tracefs_remove(struct dentry *dentry)
{
	struct dentry *parent;
	int ret;

	if (IS_ERR_OR_NULL(dentry))
		return;

	parent = dentry->d_parent;
	if (!parent || !parent->d_inode)
		return;

	mutex_lock(&parent->d_inode->i_mutex);
	ret = __tracefs_remove(dentry, parent);
	mutex_unlock(&parent->d_inode->i_mutex);
	if (!ret)
		simple_release_fs(&tracefs_mount, &tracefs_mount_count);
}
