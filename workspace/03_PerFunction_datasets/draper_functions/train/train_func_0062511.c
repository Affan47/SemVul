ttm_page_pool_fill_locked(struct ttm_page_pool *pool,
		int ttm_flags, enum ttm_caching_state cstate, unsigned count,
		unsigned long *irq_flags)
{
	struct page *p;
	int r;
	unsigned cpages = 0;


	if (pool->fill_lock)
		return;

	pool->fill_lock = true;


	if (count < _manager->options.small
		&& count > pool->npages) {
		struct list_head new_pages;
		unsigned alloc_size = _manager->options.alloc_size;


		spin_unlock_irqrestore(&pool->lock, *irq_flags);

		INIT_LIST_HEAD(&new_pages);
		r = ttm_alloc_new_pages(&new_pages, pool->gfp_flags, ttm_flags,
				cstate,	alloc_size);
		spin_lock_irqsave(&pool->lock, *irq_flags);

		if (!r) {
			list_splice(&new_pages, &pool->list);
			++pool->nrefills;
			pool->npages += alloc_size;
		} else {
			pr_err("Failed to fill pool (%p)\n", pool);

			list_for_each_entry(p, &new_pages, lru) {
				++cpages;
			}
			list_splice(&new_pages, &pool->list);
			pool->npages += cpages;
		}

	}
	pool->fill_lock = false;
}
