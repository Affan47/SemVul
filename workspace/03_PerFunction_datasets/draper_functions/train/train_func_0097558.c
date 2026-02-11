unlink_block(KEY_CACHE *keycache, BLOCK_LINK *block)
{
  DBUG_ASSERT((block->status & ~BLOCK_CHANGED) == (BLOCK_READ | BLOCK_IN_USE));
  DBUG_ASSERT(block->hash_link);
  DBUG_ASSERT(!block->requests);
  DBUG_ASSERT(block->prev_changed && *block->prev_changed == block);
  DBUG_ASSERT(block->next_used && block->prev_used &&
              (block->next_used->prev_used == &block->next_used) &&
              (*block->prev_used == block));
  if (block->next_used == block)

    keycache->used_last= keycache->used_ins= NULL;
  else
  {
    block->next_used->prev_used= block->prev_used;
    *block->prev_used= block->next_used;
    if (keycache->used_last == block)
      keycache->used_last= STRUCT_PTR(BLOCK_LINK, next_used, block->prev_used);
    if (keycache->used_ins == block)
      keycache->used_ins=STRUCT_PTR(BLOCK_LINK, next_used, block->prev_used);
  }
  block->next_used= NULL;
#if !defined(DBUG_OFF)


  block->prev_used= NULL;
#endif

  KEYCACHE_THREAD_TRACE("unlink_block");
#if defined(KEYCACHE_DEBUG)
  KEYCACHE_DBUG_ASSERT(keycache->blocks_available != 0);
  keycache->blocks_available--;
  KEYCACHE_DBUG_PRINT("unlink_block",
    ("unlinked block %u  status=%x   #requests=%u  #available=%u",
     BLOCK_NUMBER(block), block->status,
     block->requests, keycache->blocks_available));
#endif
}
