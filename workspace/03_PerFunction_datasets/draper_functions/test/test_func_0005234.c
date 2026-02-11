debugfs_read_inode_full(ext2_ino_t ino, struct ext2_inode * inode,
			const char *cmd, int bufsize)
{
	int retval;

	retval = ext2fs_read_inode_full(current_fs, ino, inode, bufsize);
	if (retval) {
		com_err(cmd, retval, "while reading inode %u", ino);
		return 1;
	}
	return 0;
}
