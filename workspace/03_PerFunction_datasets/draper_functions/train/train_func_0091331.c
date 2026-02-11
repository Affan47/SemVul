free_blocks(struct block_group_info *bg, u32 num_blocks)
{
	unsigned int i;
	u32 block = bg->first_free_block - 1;
	for (i = 0; i < num_blocks; i++, block--)
		bg->block_bitmap[block / 8] &= ~(1 << (block % 8));
	bg->free_blocks += num_blocks;
	bg->first_free_block -= num_blocks;
}
