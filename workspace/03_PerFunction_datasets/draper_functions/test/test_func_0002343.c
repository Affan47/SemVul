hfsplus_listxattr_finder_info(struct dentry *dentry,
						char *buffer, size_t size)
{
	ssize_t res = 0;
	struct inode *inode = d_inode(dentry);
	struct hfs_find_data fd;
	u16 entry_type;
	u8 folder_finder_info[sizeof(struct DInfo) + sizeof(struct DXInfo)];
	u8 file_finder_info[sizeof(struct FInfo) + sizeof(struct FXInfo)];
	unsigned long len, found_bit;
	int xattr_name_len, symbols_count;

	res = hfs_find_init(HFSPLUS_SB(inode->i_sb)->cat_tree, &fd);
	if (res) {
		pr_err("can't init xattr find struct\n");
		return res;
	}

	res = hfsplus_find_cat(inode->i_sb, inode->i_ino, &fd);
	if (res)
		goto end_listxattr_finder_info;

	entry_type = hfs_bnode_read_u16(fd.bnode, fd.entryoffset);
	if (entry_type == HFSPLUS_FOLDER) {
		len = sizeof(struct DInfo) + sizeof(struct DXInfo);
		hfs_bnode_read(fd.bnode, folder_finder_info,
				fd.entryoffset +
				offsetof(struct hfsplus_cat_folder, user_info),
				len);
		found_bit = find_first_bit((void *)folder_finder_info, len*8);
	} else if (entry_type == HFSPLUS_FILE) {
		len = sizeof(struct FInfo) + sizeof(struct FXInfo);
		hfs_bnode_read(fd.bnode, file_finder_info,
				fd.entryoffset +
				offsetof(struct hfsplus_cat_file, user_info),
				len);
		found_bit = find_first_bit((void *)file_finder_info, len*8);
	} else {
		res = -EOPNOTSUPP;
		goto end_listxattr_finder_info;
	}

	if (found_bit >= (len*8))
		res = 0;
	else {
		symbols_count = sizeof(HFSPLUS_XATTR_FINDER_INFO_NAME) - 1;
		xattr_name_len =
			name_len(HFSPLUS_XATTR_FINDER_INFO_NAME, symbols_count);
		if (!buffer || !size) {
			if (can_list(HFSPLUS_XATTR_FINDER_INFO_NAME))
				res = xattr_name_len;
		} else if (can_list(HFSPLUS_XATTR_FINDER_INFO_NAME)) {
			if (size < xattr_name_len)
				res = -ERANGE;
			else {
				res = copy_name(buffer,
						HFSPLUS_XATTR_FINDER_INFO_NAME,
						symbols_count);
			}
		}
	}

end_listxattr_finder_info:
	hfs_find_exit(&fd);

	return res;
}
