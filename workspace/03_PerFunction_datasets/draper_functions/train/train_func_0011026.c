close_filesystem(NOARGS)
{
	int	retval;

	if (current_fs->flags & EXT2_FLAG_IB_DIRTY) {
		retval = ext2fs_write_inode_bitmap(current_fs);
		if (retval)
			com_err("ext2fs_write_inode_bitmap", retval, 0);
	}
	if (current_fs->flags & EXT2_FLAG_BB_DIRTY) {
		retval = ext2fs_write_block_bitmap(current_fs);
		if (retval)
			com_err("ext2fs_write_block_bitmap", retval, 0);
	}
	retval = ext2fs_close(current_fs);
	if (retval)
		com_err("ext2fs_close", retval, 0);
	current_fs = NULL;
	return;
}
