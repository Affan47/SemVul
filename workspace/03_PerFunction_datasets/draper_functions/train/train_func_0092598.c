free_hot_cold_page(struct page *page, bool cold)
{
	struct zone *zone = page_zone(page);
	struct per_cpu_pages *pcp;
	unsigned long flags;
	unsigned long pfn = page_to_pfn(page);
	int migratetype;

	if (!free_pages_prepare(page, 0))
		return;

	migratetype = get_pfnblock_migratetype(page, pfn);
	set_pcppage_migratetype(page, migratetype);
	local_irq_save(flags);
	__count_vm_event(PGFREE);


	if (migratetype >= MIGRATE_PCPTYPES) {
		if (unlikely(is_migrate_isolate(migratetype))) {
			free_one_page(zone, page, pfn, 0, migratetype);
			goto out;
		}
		migratetype = MIGRATE_MOVABLE;
	}

	pcp = &this_cpu_ptr(zone->pageset)->pcp;
	if (!cold)
		list_add(&page->lru, &pcp->lists[migratetype]);
	else
		list_add_tail(&page->lru, &pcp->lists[migratetype]);
	pcp->count++;
	if (pcp->count >= pcp->high) {
		unsigned long batch = READ_ONCE(pcp->batch);
		free_pcppages_bulk(zone, batch, pcp);
		pcp->count -= batch;
	}

out:
	local_irq_restore(flags);
}
