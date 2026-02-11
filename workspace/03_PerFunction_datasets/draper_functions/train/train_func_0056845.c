ufs1_read_inode(struct inode *inode, struct ufs_inode *ufs_inode)
{
	struct ufs_inode_info *ufsi = UFS_I(inode);
	struct super_block *sb = inode->i_sb;
	umode_t mode;


	inode->i_mode = mode = fs16_to_cpu(sb, ufs_inode->ui_mode);
	set_nlink(inode, fs16_to_cpu(sb, ufs_inode->ui_nlink));
	if (inode->i_nlink == 0) {
		ufs_error (sb, "ufs_read_inode", "inode %lu has zero nlink\n", inode->i_ino);
		return -1;
	}


	i_uid_write(inode, ufs_get_inode_uid(sb, ufs_inode));
	i_gid_write(inode, ufs_get_inode_gid(sb, ufs_inode));

	inode->i_size = fs64_to_cpu(sb, ufs_inode->ui_size);
	inode->i_atime.tv_sec = fs32_to_cpu(sb, ufs_inode->ui_atime.tv_sec);
	inode->i_ctime.tv_sec = fs32_to_cpu(sb, ufs_inode->ui_ctime.tv_sec);
	inode->i_mtime.tv_sec = fs32_to_cpu(sb, ufs_inode->ui_mtime.tv_sec);
	inode->i_mtime.tv_nsec = 0;
	inode->i_atime.tv_nsec = 0;
	inode->i_ctime.tv_nsec = 0;
	inode->i_blocks = fs32_to_cpu(sb, ufs_inode->ui_blocks);
	inode->i_generation = fs32_to_cpu(sb, ufs_inode->ui_gen);
	ufsi->i_flags = fs32_to_cpu(sb, ufs_inode->ui_flags);
	ufsi->i_shadow = fs32_to_cpu(sb, ufs_inode->ui_u3.ui_sun.ui_shadow);
	ufsi->i_oeftflag = fs32_to_cpu(sb, ufs_inode->ui_u3.ui_sun.ui_oeftflag);


	if (S_ISCHR(mode) || S_ISBLK(mode) || inode->i_blocks) {
		memcpy(ufsi->i_u1.i_data, &ufs_inode->ui_u2.ui_addr,
		       sizeof(ufs_inode->ui_u2.ui_addr));
	} else {
		memcpy(ufsi->i_u1.i_symlink, ufs_inode->ui_u2.ui_symlink,
		       sizeof(ufs_inode->ui_u2.ui_symlink) - 1);
		ufsi->i_u1.i_symlink[sizeof(ufs_inode->ui_u2.ui_symlink) - 1] = 0;
	}
	return 0;
}
