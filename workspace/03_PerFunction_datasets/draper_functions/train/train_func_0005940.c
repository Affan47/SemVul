git_pool_malloc(git_pool *pool, uint32_t items)
{
	git_pool_page *scan = pool->open, *prev;
	uint32_t size = ((items * pool->item_size) + 7) & ~7;
	void *ptr = NULL;

	pool->has_string_alloc = 0;
	if (items > 1)
		pool->has_multi_item_alloc = 1;
	else if (pool->free_list != NULL) {
		ptr = pool->free_list;
		pool->free_list = ((struct pool_freelist *)pool->free_list)->next;
		return ptr;
	}


	if (size >= pool->page_size || !scan || scan->avail < size)
		return pool_alloc_page(pool, size);

	pool->items++;


	for (scan = pool->open, prev = NULL;
		 scan->next && scan->next->avail >= size;
		 prev = scan, scan = scan->next);


	ptr = &scan->data[scan->size - scan->avail];
	scan->avail -= size;


	if (scan->avail < pool->item_size || scan->avail < GIT_POOL_MIN_USABLE) {
		pool_remove_page(pool, scan, prev);
		scan->next = pool->full;
		pool->full = scan;
	}

	else if (scan->next != NULL && scan->next->avail > scan->avail) {
		pool_remove_page(pool, scan, prev);
		pool_insert_page(pool, scan);
	}

	return ptr;
}
