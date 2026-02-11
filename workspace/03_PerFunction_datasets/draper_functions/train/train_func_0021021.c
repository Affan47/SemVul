recover_inode(struct inode *inode, struct page *page)
{
	struct f2fs_inode *raw = F2FS_INODE(page);
	char *name;

	inode->i_mode = le16_to_cpu(raw->i_mode);
	i_size_write(inode, le64_to_cpu(raw->i_size));
	inode->i_atime.tv_sec = le64_to_cpu(raw->i_mtime);
	inode->i_ctime.tv_sec = le64_to_cpu(raw->i_ctime);
	inode->i_mtime.tv_sec = le64_to_cpu(raw->i_mtime);
	inode->i_atime.tv_nsec = le32_to_cpu(raw->i_mtime_nsec);
	inode->i_ctime.tv_nsec = le32_to_cpu(raw->i_ctime_nsec);
	inode->i_mtime.tv_nsec = le32_to_cpu(raw->i_mtime_nsec);

	if (file_enc_name(inode))
		name = "<encrypted>";
	else
		name = F2FS_INODE(page)->i_name;

	f2fs_msg(inode->i_sb, KERN_NOTICE, "recover_inode: ino = %x, name = %s",
			ino_of_node(page), name);
}
