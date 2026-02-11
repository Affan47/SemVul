nfs_getattr(struct vfsmount *mnt, struct dentry *dentry, struct kstat *stat)
{
	struct inode *inode = d_inode(dentry);
	int need_atime = NFS_I(inode)->cache_validity & NFS_INO_INVALID_ATIME;
	int err = 0;

	trace_nfs_getattr_enter(inode);

	if (S_ISREG(inode->i_mode)) {
		mutex_lock(&inode->i_mutex);
		err = nfs_sync_inode(inode);
		mutex_unlock(&inode->i_mutex);
		if (err)
			goto out;
	}


 	if ((mnt->mnt_flags & MNT_NOATIME) ||
 	    ((mnt->mnt_flags & MNT_NODIRATIME) && S_ISDIR(inode->i_mode)))
		need_atime = 0;

	if (need_atime || nfs_need_revalidate_inode(inode)) {
		struct nfs_server *server = NFS_SERVER(inode);

		if (server->caps & NFS_CAP_READDIRPLUS)
			nfs_request_parent_use_readdirplus(dentry);
		err = __nfs_revalidate_inode(server, inode);
	}
	if (!err) {
		generic_fillattr(inode, stat);
		stat->ino = nfs_compat_user_ino64(NFS_FILEID(inode));
		if (S_ISDIR(inode->i_mode))
			stat->blksize = NFS_SERVER(inode)->dtsize;
	}
out:
	trace_nfs_getattr_exit(inode, err);
	return err;
}
