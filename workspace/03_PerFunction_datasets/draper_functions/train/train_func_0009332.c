cuddCacheLookup2Zdd(
  DdManager * table,
  DD_CTFP op,
  DdNode * f,
  DdNode * g)
{
    int posn;
    DdCache *en,*cache;
    DdNode *data;

    cache = table->cache;
#ifdef DD_DEBUG
    if (cache == NULL) {
	return(NULL);
    }
#endif

    posn = ddCHash2(op,f,g,table->cacheShift);
    en = &cache[posn];
    if (en->data != NULL && en->f==f && en->g==g && en->h==(ptruint)op) {
	data = Cudd_Regular(en->data);
	table->cacheHits++;
	if (data->ref == 0) {
	    cuddReclaimZdd(table,data);
	}
	return(en->data);
    }


    table->cacheMisses++;

    if (table->cacheSlack >= 0 &&
	table->cacheHits > table->cacheMisses * table->minHit) {
	cuddCacheResize(table);
    }

    return(NULL);

}
