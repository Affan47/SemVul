ext2fs_get_blocks(ext2_filsys fs, ext2_ino_t ino, blk_t *blocks)
{
	struct ext2_inode	inode;
	int			i;
	errcode_t		retval;

	EXT2_CHECK_MAGIC(fs, EXT2_ET_MAGIC_EXT2FS_FILSYS);

	if (ino > fs->super->s_inodes_count)
		return EXT2_ET_BAD_INODE_NUM;

	if (fs->get_blocks) {
		if (!(*fs->get_blocks)(fs, ino, blocks))
			return 0;
	}
	retval = ext2fs_read_inode(fs, ino, &inode);
	if (retval)
		return retval;
	for (i=0; i < EXT2_N_BLOCKS; i++)
		blocks[i] = inode.i_block[i];
	return 0;
}
