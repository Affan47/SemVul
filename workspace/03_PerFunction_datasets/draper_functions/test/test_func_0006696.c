ext2fs_mark_block_bitmap_range(ext2fs_block_bitmap bitmap,
				    blk_t block, int num)
{
	int	i;

	if ((block < bitmap->start) || (block+num-1 > bitmap->end)) {
		ext2fs_warn_bitmap(EXT2_ET_BAD_BLOCK_MARK, block,
				   bitmap->description);
		return;
	}
	for (i=0; i < num; i++)
		ext2fs_fast_set_bit(block + i - bitmap->start, bitmap->bitmap);
}
