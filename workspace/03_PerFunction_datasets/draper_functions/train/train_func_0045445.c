cha_block_new_item(cha_block_t *block)
{
    if (++block->num > block->allocated_num) {
	block->allocated_num *= 2;
	block->blocks = cha_realloc(block->blocks,
				    block->item_size * block->allocated_num);
    }
    return block->blocks + block->item_size * (block->num - 1);
}
