cache_zap(cache_t cache)
{
	__cache_t *c = cache;
	if (!c)
		return;
	while (!list_empty(&c->list))
		cache_e_free(cache, (__cache_e_t *)(c->list.next));
	while (!list_empty(&c->unused))
		cache_e_free(cache, (__cache_e_t *)(c->unused.next));
	c->size = 0;
	c->used = 0;
}
