process_block(ext2_filsys fs EXT2FS_ATTR((unused)),
			 blk_t *block_nr,
			 e2_blkcnt_t blockcnt EXT2FS_ATTR((unused)),
			 blk_t ref_block EXT2FS_ATTR((unused)),
			 int ref_offset EXT2FS_ATTR((unused)),
			 void *priv_data)
{
	int ret = 0;
	blk_t new_blk;
	ext2fs_block_bitmap bmap = (ext2fs_block_bitmap) priv_data;

	if (!ext2fs_test_block_bitmap(bmap, *block_nr))
		return 0;
	new_blk = translate_block(*block_nr);
	if (new_blk) {
		*block_nr = new_blk;


		ret |= BLOCK_CHANGED;
	}

	return ret;
}
