BlockHeapDestroy(BlockHeap *bh)
{
  Block *walker = NULL, *next = NULL;

  if (bh == NULL)
    return 1;

  for (walker = bh->base; walker != NULL; walker = next)
  {
    next = walker->next;
    free_block(walker->elems, walker->alloc_size);

    if (walker != NULL)
      free(walker);
  }

  if (heap_list == bh)
    heap_list = bh->next;
  else {
    BlockHeap *prev;

    for (prev = heap_list; prev->next != bh; prev = prev->next)
       ;
    prev->next = bh->next;
  }

  free(bh);
  return 0;
}
