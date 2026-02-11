create_alloc_pool (const char *name, size_t size, size_t num)
{
  alloc_pool pool;
  size_t pool_size, header_size;
#ifdef GATHER_STATISTICS
  struct alloc_pool_descriptor *desc;
#endif

  if (!name)
    abort ();


  if (size < sizeof (alloc_pool_list))
    size = sizeof (alloc_pool_list);


  size = align_eight (size);

#ifdef ENABLE_CHECKING

  size += offsetof (allocation_object, u.data);
#endif


  if (num == 0)
    abort ();


  pool_size = sizeof (struct alloc_pool_def);


  pool = xmalloc (pool_size);


  pool->name = name;
#ifdef GATHER_STATISTICS
  desc = alloc_pool_descriptor (name);
  desc->created++;
#endif
  pool->elt_size = size;
  pool->elts_per_block = num;


  header_size = align_eight (sizeof (struct alloc_pool_list_def));

  pool->block_size = (size * num) + header_size;
  pool->free_list = NULL;
  pool->elts_allocated = 0;
  pool->elts_free = 0;
  pool->blocks_allocated = 0;
  pool->block_list = NULL;

#ifdef ENABLE_CHECKING


  last_id++;
  if (last_id == 0)
    last_id++;

  pool->id = last_id;
#endif

  return (pool);
}
