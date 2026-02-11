hfs_inode_setattr(struct dentry *dentry, struct iattr * attr)
{
	struct inode *inode = d_inode(dentry);
	struct hfs_sb_info *hsb = HFS_SB(inode->i_sb);
	int error;

	error = inode_change_ok(inode, attr);
	if (error)
		return error;


	if (((attr->ia_valid & ATTR_UID) &&
	     (!uid_eq(attr->ia_uid, hsb->s_uid))) ||
	    ((attr->ia_valid & ATTR_GID) &&
	     (!gid_eq(attr->ia_gid, hsb->s_gid))) ||
	    ((attr->ia_valid & ATTR_MODE) &&
	     ((S_ISDIR(inode->i_mode) &&
	       (attr->ia_mode != inode->i_mode)) ||
	      (attr->ia_mode & ~HFS_VALID_MODE_BITS)))) {
		return hsb->s_quiet ? 0 : error;
	}

	if (attr->ia_valid & ATTR_MODE) {

		if (attr->ia_mode & S_IWUSR)
			attr->ia_mode = inode->i_mode | S_IWUGO;
		else
			attr->ia_mode = inode->i_mode & ~S_IWUGO;
		attr->ia_mode &= S_ISDIR(inode->i_mode) ? ~hsb->s_dir_umask: ~hsb->s_file_umask;
	}

	if ((attr->ia_valid & ATTR_SIZE) &&
	    attr->ia_size != i_size_read(inode)) {
		inode_dio_wait(inode);

		error = inode_newsize_ok(inode, attr->ia_size);
		if (error)
			return error;

		truncate_setsize(inode, attr->ia_size);
		hfs_file_truncate(inode);
	}

	setattr_copy(inode, attr);
	mark_inode_dirty(inode);
	return 0;
}
