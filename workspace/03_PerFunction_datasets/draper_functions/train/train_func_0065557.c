e2fsck_pass1_check_device_inode(ext2_filsys fs EXT2FS_ATTR((unused)),
				    struct ext2_inode *inode)
{
	int	i;


	if (inode->i_flags & EXT2_INDEX_FL)
		return 0;


	if (inode->i_flags & (EXT2_IMMUTABLE_FL | EXT2_APPEND_FL)) {
		for (i=4; i < EXT2_N_BLOCKS; i++)
			if (inode->i_block[i])
				return 0;
	}
	return 1;
}
