kill_file_by_inode(ext2_ino_t inode)
{
	struct ext2_inode inode_buf;

	if (debugfs_read_inode(inode, &inode_buf, 0))
		return;
	inode_buf.i_dtime = current_fs->now ? current_fs->now : time(0);
	if (debugfs_write_inode(inode, &inode_buf, 0))
		return;
	if (!ext2fs_inode_has_valid_blocks(&inode_buf))
		return;

	ext2fs_block_iterate(current_fs, inode, BLOCK_FLAG_READ_ONLY, NULL,
			     release_blocks_proc, NULL);
	printf("\n");
	ext2fs_inode_alloc_stats2(current_fs, inode, -1,
				  LINUX_S_ISDIR(inode_buf.i_mode));
}
