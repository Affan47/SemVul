kernfs_iop_setattr(struct dentry *dentry, struct iattr *iattr)
{
	struct inode *inode = d_inode(dentry);
	struct kernfs_node *kn = dentry->d_fsdata;
	int error;

	if (!kn)
		return -EINVAL;

	mutex_lock(&kernfs_mutex);
	error = inode_change_ok(inode, iattr);
	if (error)
		goto out;

	error = __kernfs_setattr(kn, iattr);
	if (error)
		goto out;


	setattr_copy(inode, iattr);

out:
	mutex_unlock(&kernfs_mutex);
	return error;
}
