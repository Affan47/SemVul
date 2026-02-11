jfs_listxattr(struct dentry * dentry, char *data, size_t buf_size)
{
	struct inode *inode = d_inode(dentry);
	char *buffer;
	ssize_t size = 0;
	int xattr_size;
	struct jfs_ea_list *ealist;
	struct jfs_ea *ea;
	struct ea_buffer ea_buf;

	down_read(&JFS_IP(inode)->xattr_sem);

	xattr_size = ea_get(inode, &ea_buf, 0);
	if (xattr_size < 0) {
		size = xattr_size;
		goto out;
	}

	if (xattr_size == 0)
		goto release;

	ealist = (struct jfs_ea_list *) ea_buf.xattr;


	for (ea = FIRST_EA(ealist); ea < END_EALIST(ealist); ea = NEXT_EA(ea)) {
		if (can_list(ea))
			size += name_size(ea) + 1;
	}

	if (!data)
		goto release;

	if (size > buf_size) {
		size = -ERANGE;
		goto release;
	}


	buffer = data;
	for (ea = FIRST_EA(ealist); ea < END_EALIST(ealist); ea = NEXT_EA(ea)) {
		if (can_list(ea)) {
			int namelen = copy_name(buffer, ea);
			buffer += namelen + 1;
		}
	}

      release:
	ea_release(inode, &ea_buf);
      out:
	up_read(&JFS_IP(inode)->xattr_sem);
	return size;
}
