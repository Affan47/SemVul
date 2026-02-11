obj_is_from_pinned_alloc (char *ptr)
{
	MSBlockInfo *block;

	FOREACH_BLOCK (block) {
		if (ptr >= block->block && ptr <= block->block + MS_BLOCK_SIZE)
			return block->pinned;
	} END_FOREACH_BLOCK;
	return FALSE;
}
