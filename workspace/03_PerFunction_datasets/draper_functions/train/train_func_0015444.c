check_bb_inode_blocks(ext2_filsys fs,
				 blk_t *block_nr,
				 int blockcnt EXT2FS_ATTR((unused)),
				 void *priv_data EXT2FS_ATTR((unused)))
{
	if (!*block_nr)
		return 0;


	if (*block_nr >= fs->super->s_blocks_count ||
	    *block_nr < fs->super->s_first_data_block) {
		printf(_("Warning: illegal block %u found in bad block inode.  "
			 "Cleared.\n"), *block_nr);
		*block_nr = 0;
		return BLOCK_CHANGED;
	}

	return 0;
}
