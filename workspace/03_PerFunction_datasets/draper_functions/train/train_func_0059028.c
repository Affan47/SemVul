cache_init(int size, cache_free_fn free_fn)
{
	int i = 0;
	__cache_t *c = malloc(sizeof(__cache_t));
	if (!c)
		return NULL;
	INIT_LIST_HEAD(&c->list);
	INIT_LIST_HEAD(&c->unused);
	c->auto_grow = 0;
	c->size = 0;
	c->used = 0;
	if (!size)
		c->auto_grow = 1;
	c->max_size = size;
	c->free_fn = free_fn;
	for (i = 0; i < HASH_SIZE; i++) {
			INIT_LIST_HEAD(&c->hash[i]);
			INIT_LIST_HEAD(&c->vhash[i]);
	}
	return (cache_t)c;
}
