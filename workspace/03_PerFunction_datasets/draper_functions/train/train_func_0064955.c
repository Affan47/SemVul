lj_gc_freeall(global_State *g)
{
  MSize i, strmask;

  g->gc.currentwhite = LJ_GC_WHITES | LJ_GC_SFIXED;
  gc_fullsweep(g, &g->gc.root);
  strmask = g->strmask;
  for (i = 0; i <= strmask; i++)
    gc_fullsweep(g, &g->strhash[i]);
}
