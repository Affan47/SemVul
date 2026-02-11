ext2fs_get_free_blocks(ext2_filsys fs, blk_t start, blk_t finish,
				 int num, ext2fs_block_bitmap map, blk_t *ret)
{
	errcode_t retval;
	blk64_t val;
	retval = ext2fs_get_free_blocks2(fs, start, finish, num, map, &val);
	if(!retval)
		*ret = (blk_t) val;
	return retval;
}
