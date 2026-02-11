pool_alloc (alloc_pool pool)
{
  alloc_pool_list header;
  char *block;
#ifdef GATHER_STATISTICS
  struct alloc_pool_descriptor *desc = alloc_pool_descriptor (pool->name);

  desc->allocated+=pool->elt_size;
#endif

#ifdef ENABLE_CHECKING
  if (!pool)
    abort ();
#endif


  if (!pool->free_list)
    {
      size_t i;
      alloc_pool_list block_header;


      block = xmalloc (pool->block_size);
      block_header = (alloc_pool_list) block;
      block += align_eight (sizeof (struct alloc_pool_list_def));
#ifdef GATHER_STATISTICS
      desc->current += pool->block_size;
      if (desc->peak < desc->current)
	desc->peak = desc->current;
#endif


      block_header->next = pool->block_list;
      pool->block_list = block_header;


      for (i = 0; i < pool->elts_per_block; i++, block += pool->elt_size)
      {
#ifdef ENABLE_CHECKING

	((allocation_object *) block)->id = 0;
#endif
        header = (alloc_pool_list) USER_PTR_FROM_ALLOCATION_OBJECT_PTR (block);
        header->next = pool->free_list;
        pool->free_list = header;
      }


      pool->elts_allocated += pool->elts_per_block;
      pool->elts_free += pool->elts_per_block;
      pool->blocks_allocated += 1;
    }


  header = pool->free_list;
  pool->free_list = header->next;
  pool->elts_free--;

#ifdef ENABLE_CHECKING

  ALLOCATION_OBJECT_PTR_FROM_USER_PTR (header)->id = pool->id;
#endif

  return ((void *) header);
}
