cuddCacheLookup(
  DdManager * table,
  ptruint op,
  DdNode * f,
  DdNode * g,
  DdNode * h)
{
    int posn;
    DdCache *en,*cache;
    DdNode *data;
    ptruint uf, ug, uh;

    uf = (ptruint) f | (op & 0xe);
    ug = (ptruint) g | (op >> 4);
    uh = (ptruint) h;

    cache = table->cache;
#ifdef DD_DEBUG
    if (cache == NULL) {
	return(NULL);
    }
#endif

    posn = ddCHash2(uh,uf,ug,table->cacheShift);
    en = &cache[posn];
    if (en->data != NULL && en->f==(DdNodePtr)uf && en->g==(DdNodePtr)ug &&
	en->h==uh) {
	data = Cudd_Regular(en->data);
	table->cacheHits++;
	if (data->ref == 0) {
	    cuddReclaim(table,data);
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
