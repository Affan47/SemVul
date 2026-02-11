ecryptfs_removexattr(struct dentry *dentry, const char *name)
{
	int rc = 0;
	struct dentry *lower_dentry;

	lower_dentry = ecryptfs_dentry_to_lower(dentry);
	if (!d_inode(lower_dentry)->i_op->removexattr) {
		rc = -EOPNOTSUPP;
		goto out;
	}
	mutex_lock(&d_inode(lower_dentry)->i_mutex);
	rc = d_inode(lower_dentry)->i_op->removexattr(lower_dentry, name);
	mutex_unlock(&d_inode(lower_dentry)->i_mutex);
out:
	return rc;
}
