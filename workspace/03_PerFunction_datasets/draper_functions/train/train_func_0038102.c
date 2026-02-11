nfs_neg_need_reval(struct inode *dir, struct dentry *dentry,
		       unsigned int flags)
{

	if (flags & LOOKUP_CREATE)
		return 0;
	if (NFS_SERVER(dir)->flags & NFS_MOUNT_LOOKUP_CACHE_NONEG)
		return 1;
	return !nfs_check_verifier(dir, dentry, flags & LOOKUP_RCU);
}
