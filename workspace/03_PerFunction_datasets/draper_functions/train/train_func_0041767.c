undo_memory_block_coalesce_free (UNDO_BLOCK * block)
{
  void *last, *mem;

  last = NULL;
  FOREACH_IN_BLOCK (*block, mem)
  {
    if (last == NULL)
      {
	last = mem;
	continue;
      }

    if (!MEMORY_USED (last) && !MEMORY_USED (mem))
      {
	MEMORY_SET_SIZE_USED (last,
			      MEMORY_SIZE (last) + MEMORY_SIZE (mem), 0);
	continue;
      }

    last = mem;
  }
}
