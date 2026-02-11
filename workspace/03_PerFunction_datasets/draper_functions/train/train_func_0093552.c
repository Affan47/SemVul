_pool_new(char *zone, int line)
{
    pool_t p;
    while((p = _pool__malloc(sizeof(_pool))) == NULL) sleep(1);
    p->cleanup = NULL;
    p->heap = NULL;
    p->size = 0;

#ifdef POOL_DEBUG
    p->lsize = -1;
    p->zone[0] = '\0';
    snprintf(p->zone, sizeof(p->zone), "%s:%i", zone, line);
    sprintf(p->name,"%X",(int)p);

    if(pool__disturbed == NULL)
    {
        pool__disturbed = (xht)1;
	pool__disturbed = xhash_new(POOL_NUM);
    }
    if(pool__disturbed != (xht)1)
        xhash_put(pool__disturbed,p->name,p);
#endif

    return p;
}
