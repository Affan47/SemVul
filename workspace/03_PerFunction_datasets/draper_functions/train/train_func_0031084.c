gc_alloc_pair(void *a, void *d)
{
  if (!gc.pairs_freelist)
    {
      gc_run();
      if (!gc.pairs_freelist)
        new_pair_block();
    }
  else if (gc.debug)
    gc_run();
  void **p = gc.pairs_freelist;
  gc.pairs_freelist = (void**)p[0];
  gc.pairs_free -= 1;
  p[0] = a;
  p[1] = d;
  return p;
}
