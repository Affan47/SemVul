replace_page_cache_page(struct page *old, struct page *new, gfp_t gfp_mask)
{
	int error;

	VM_BUG_ON_PAGE(!PageLocked(old), old);
	VM_BUG_ON_PAGE(!PageLocked(new), new);
	VM_BUG_ON_PAGE(new->mapping, new);

	error = radix_tree_preload(gfp_mask & ~__GFP_HIGHMEM);
	if (!error) {
		struct address_space *mapping = old->mapping;
		void (*freepage)(struct page *);
		struct mem_cgroup *memcg;
		unsigned long flags;

		pgoff_t offset = old->index;
		freepage = mapping->a_ops->freepage;

		page_cache_get(new);
		new->mapping = mapping;
		new->index = offset;

		memcg = mem_cgroup_begin_page_stat(old);
		spin_lock_irqsave(&mapping->tree_lock, flags);
		__delete_from_page_cache(old, NULL, memcg);
		error = page_cache_tree_insert(mapping, new, NULL);
		BUG_ON(error);


		if (!PageHuge(new))
			__inc_zone_page_state(new, NR_FILE_PAGES);
		if (PageSwapBacked(new))
			__inc_zone_page_state(new, NR_SHMEM);
		spin_unlock_irqrestore(&mapping->tree_lock, flags);
		mem_cgroup_end_page_stat(memcg);
		mem_cgroup_replace_page(old, new);
		radix_tree_preload_end();
		if (freepage)
			freepage(old);
		page_cache_release(old);
	}

	return error;
}
