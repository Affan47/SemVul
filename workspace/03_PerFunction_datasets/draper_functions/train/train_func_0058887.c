free_memory_block(Query_cache_block *block)
{
  DBUG_ENTER("Query_cache::free_memory_block");
  block->used=0;
  block->type= Query_cache_block::FREE;
  DBUG_PRINT("qcache",
	     ("first_block 0x%lx, block 0x%lx, pnext 0x%lx pprev 0x%lx",
	      (ulong) first_block, (ulong) block, (ulong) block->pnext,
	      (ulong) block->pprev));

  if (block->pnext != first_block && block->pnext->is_free())
    block = join_free_blocks(block, block->pnext);
  if (block != first_block && block->pprev->is_free())
    block = join_free_blocks(block->pprev, block->pprev);
  insert_into_free_memory_list(block);
  DBUG_VOID_RETURN;
}
