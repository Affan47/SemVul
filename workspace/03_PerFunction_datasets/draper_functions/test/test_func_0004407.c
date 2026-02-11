cuddCacheFlush(
  DdManager * table)
{
    int i, slots;
    DdCache *cache;

    slots = table->cacheSlots;
    cache = table->cache;
    for (i = 0; i < slots; i++) {
	table->cachedeletions += cache[i].data != NULL;
	cache[i].data = NULL;
    }
    table->cacheLastInserts = table->cacheinserts;

    return;

}
