nfs_safe_remove(struct dentry *dentry)
{
	struct inode *dir = d_inode(dentry->d_parent);
	struct inode *inode = d_inode(dentry);
	int error = -EBUSY;

	dfprintk(VFS, "NFS: safe_remove(%pd2)\n", dentry);


	if (dentry->d_flags & DCACHE_NFSFS_RENAMED) {
		error = 0;
		goto out;
	}

	trace_nfs_remove_enter(dir, dentry);
	if (inode != NULL) {
		NFS_PROTO(inode)->return_delegation(inode);
		error = NFS_PROTO(dir)->remove(dir, &dentry->d_name);
		if (error == 0)
			nfs_drop_nlink(inode);
	} else
		error = NFS_PROTO(dir)->remove(dir, &dentry->d_name);
	if (error == -ENOENT)
		nfs_dentry_handle_enoent(dentry);
	trace_nfs_remove_exit(dir, dentry, error);
out:
	return error;
}
