nfs_setattr(struct dentry *dentry, struct iattr *attr)
{
	struct inode *inode = d_inode(dentry);
	struct nfs_fattr *fattr;
	int error = 0;

	nfs_inc_stats(inode, NFSIOS_VFSSETATTR);


	if (attr->ia_valid & (ATTR_KILL_SUID | ATTR_KILL_SGID))
		attr->ia_valid &= ~ATTR_MODE;

	if (attr->ia_valid & ATTR_SIZE) {
		BUG_ON(!S_ISREG(inode->i_mode));

		error = inode_newsize_ok(inode, attr->ia_size);
		if (error)
			return error;

		if (attr->ia_size == i_size_read(inode))
			attr->ia_valid &= ~ATTR_SIZE;
	}


	attr->ia_valid &= NFS_VALID_ATTRS;
	if ((attr->ia_valid & ~(ATTR_FILE|ATTR_OPEN)) == 0)
		return 0;

	trace_nfs_setattr_enter(inode);


	if (S_ISREG(inode->i_mode))
		nfs_sync_inode(inode);

	fattr = nfs_alloc_fattr();
	if (fattr == NULL) {
		error = -ENOMEM;
		goto out;
	}


	if ((attr->ia_valid & (ATTR_MODE|ATTR_UID|ATTR_GID)) != 0)
		NFS_PROTO(inode)->return_delegation(inode);
	error = NFS_PROTO(inode)->setattr(dentry, fattr, attr);
	if (error == 0)
		error = nfs_refresh_inode(inode, fattr);
	nfs_free_fattr(fattr);
out:
	trace_nfs_setattr_exit(inode, error);
	return error;
}
