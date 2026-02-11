_idle_FreeListNodes(FreeList *fl)
{
  return fl ? (fl->ntotal - fl->nbusy) : 0;
}
