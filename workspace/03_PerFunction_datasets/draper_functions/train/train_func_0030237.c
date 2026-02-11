ttm_dma_page_pool_free(struct dma_pool *pool, unsigned nr_free,
				       bool use_static)
{
	static struct page *static_buf[NUM_PAGES_TO_ALLOC];
	unsigned long irq_flags;
	struct dma_page *dma_p, *tmp;
	struct page **pages_to_free;
	struct list_head d_pages;
	unsigned freed_pages = 0,
		 npages_to_free = nr_free;

	if (NUM_PAGES_TO_ALLOC < nr_free)
		npages_to_free = NUM_PAGES_TO_ALLOC;
#if 0
	if (nr_free > 1) {
		pr_debug("%s: (%s:%d) Attempting to free %d (%d) pages\n",
			 pool->dev_name, pool->name, current->pid,
			 npages_to_free, nr_free);
	}
#endif
	if (use_static)
		pages_to_free = static_buf;
	else
		pages_to_free = kmalloc(npages_to_free * sizeof(struct page *),
					GFP_KERNEL);

	if (!pages_to_free) {
		pr_err("%s: Failed to allocate memory for pool free operation\n",
		       pool->dev_name);
		return 0;
	}
	INIT_LIST_HEAD(&d_pages);
restart:
	spin_lock_irqsave(&pool->lock, irq_flags);


	list_for_each_entry_safe_reverse(dma_p, tmp, &pool->free_list,
					 page_list) {
		if (freed_pages >= npages_to_free)
			break;


		list_move(&dma_p->page_list, &d_pages);

		pages_to_free[freed_pages++] = dma_p->p;

		if (freed_pages >= NUM_PAGES_TO_ALLOC) {

			ttm_pool_update_free_locked(pool, freed_pages);


			spin_unlock_irqrestore(&pool->lock, irq_flags);

			ttm_dma_pages_put(pool, &d_pages, pages_to_free,
					  freed_pages);

			INIT_LIST_HEAD(&d_pages);

			if (likely(nr_free != FREE_ALL_PAGES))
				nr_free -= freed_pages;

			if (NUM_PAGES_TO_ALLOC >= nr_free)
				npages_to_free = nr_free;
			else
				npages_to_free = NUM_PAGES_TO_ALLOC;

			freed_pages = 0;


			if (nr_free)
				goto restart;


			goto out;

		}
	}


	if (freed_pages) {
		ttm_pool_update_free_locked(pool, freed_pages);
		nr_free -= freed_pages;
	}

	spin_unlock_irqrestore(&pool->lock, irq_flags);

	if (freed_pages)
		ttm_dma_pages_put(pool, &d_pages, pages_to_free, freed_pages);
out:
	if (pages_to_free != static_buf)
		kfree(pages_to_free);
	return nr_free;
}
