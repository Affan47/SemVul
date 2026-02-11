cifs_strict_readv(struct kiocb *iocb, struct iov_iter *to)
{
	struct inode *inode = file_inode(iocb->ki_filp);
	struct cifsInodeInfo *cinode = CIFS_I(inode);
	struct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);
	struct cifsFileInfo *cfile = (struct cifsFileInfo *)
						iocb->ki_filp->private_data;
	struct cifs_tcon *tcon = tlink_tcon(cfile->tlink);
	int rc = -EACCES;


	if (!CIFS_CACHE_READ(cinode))
		return cifs_user_readv(iocb, to);

	if (cap_unix(tcon->ses) &&
	    (CIFS_UNIX_FCNTL_CAP & le64_to_cpu(tcon->fsUnixInfo.Capability)) &&
	    ((cifs_sb->mnt_cifs_flags & CIFS_MOUNT_NOPOSIXBRL) == 0))
		return generic_file_read_iter(iocb, to);


	down_read(&cinode->lock_sem);
	if (!cifs_find_lock_conflict(cfile, iocb->ki_pos, iov_iter_count(to),
				     tcon->ses->server->vals->shared_lock_type,
				     NULL, CIFS_READ_OP))
		rc = generic_file_read_iter(iocb, to);
	up_read(&cinode->lock_sem);
	return rc;
}
