uninitialize(void)
{
  if (!M_next)
    return;
#if CWDEBUG_DEBUG
  consistency_check();
#endif

  BlockList& list(*this);
  BlockNode* block = list.begin();
  Node const* const end = list.end();

  while (block != end && block->M_chunks.M_used_count == 0)
  {
    block->unlink();
    BlockNode* next = block->next();
    LIBCWD_TSD_DECLARATION;
    if (M_internal)
      set_alloc_checking_off(LIBCWD_TSD);
    ::operator delete(block);
    if (M_internal)
      set_alloc_checking_on(LIBCWD_TSD);
    --(*M_count_ptr);
    block = next;
  }
}
