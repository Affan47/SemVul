_pool_heap(pool p, int size)
{
	struct pheap *ret;
	struct pfree *clean;


	while ((ret = _pool__malloc(sizeof(struct pheap))) == NULL)
		sleep(1);
	while ((ret->block = _pool__malloc(size)) == NULL)
		sleep(1);
	ret->size = size;
	p->size += size;
	ret->used = 0;


	clean = _pool_free(p, _pool_heap_free, (void *)ret);
	clean->heap = ret;
	_pool_cleanup_append(p, clean);

	return ret;
}
