cifs_fattr_to_inode(struct inode *inode, struct cifs_fattr *fattr)
{
	struct cifsInodeInfo *cifs_i = CIFS_I(inode);
	struct cifs_sb_info *cifs_sb = CIFS_SB(inode->i_sb);

	cifs_revalidate_cache(inode, fattr);

	spin_lock(&inode->i_lock);
	inode->i_atime = fattr->cf_atime;
	inode->i_mtime = fattr->cf_mtime;
	inode->i_ctime = fattr->cf_ctime;
	inode->i_rdev = fattr->cf_rdev;
	cifs_nlink_fattr_to_inode(inode, fattr);
	inode->i_uid = fattr->cf_uid;
	inode->i_gid = fattr->cf_gid;


	if (inode->i_state & I_NEW ||
	    !(cifs_sb->mnt_cifs_flags & CIFS_MOUNT_DYNPERM))
		inode->i_mode = fattr->cf_mode;

	cifs_i->cifsAttrs = fattr->cf_cifsattrs;

	if (fattr->cf_flags & CIFS_FATTR_NEED_REVAL)
		cifs_i->time = 0;
	else
		cifs_i->time = jiffies;

	if (fattr->cf_flags & CIFS_FATTR_DELETE_PENDING)
		set_bit(CIFS_INO_DELETE_PENDING, &cifs_i->flags);
	else
		clear_bit(CIFS_INO_DELETE_PENDING, &cifs_i->flags);

	cifs_i->server_eof = fattr->cf_eof;


	if (is_size_safe_to_change(cifs_i, fattr->cf_eof)) {
		i_size_write(inode, fattr->cf_eof);


		inode->i_blocks = (512 - 1 + fattr->cf_bytes) >> 9;
	}
	spin_unlock(&inode->i_lock);

	if (fattr->cf_flags & CIFS_FATTR_DFS_REFERRAL)
		inode->i_flags |= S_AUTOMOUNT;
	if (inode->i_state & I_NEW)
		cifs_set_ops(inode);
}
