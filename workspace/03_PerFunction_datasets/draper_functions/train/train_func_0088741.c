fuse_getattr(struct vfsmount *mnt, struct dentry *entry,
			struct kstat *stat)
{
	struct inode *inode = d_inode(entry);
	struct fuse_conn *fc = get_fuse_conn(inode);

	if (!fuse_allow_current_process(fc))
		return -EACCES;

	return fuse_update_attributes(inode, stat, NULL, NULL);
}
