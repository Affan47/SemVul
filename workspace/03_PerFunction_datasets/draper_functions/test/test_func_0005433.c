Cudd_ReadCacheUsedSlots(
  DdManager * dd)
{
    unsigned long used = 0;
    int slots = dd->cacheSlots;
    DdCache *cache = dd->cache;
    int i;

    for (i = 0; i < slots; i++) {
	used += cache[i].h != 0;
    }

    return((double)used / (double) dd->cacheSlots);

}
