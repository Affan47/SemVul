__free_one_page(struct page *page,
		unsigned long pfn,
		struct zone *zone, unsigned int order,
		int migratetype)
{
	unsigned long page_idx;
	unsigned long combined_idx;
	unsigned long uninitialized_var(buddy_idx);
	struct page *buddy;
	unsigned int max_order;

	max_order = min_t(unsigned int, MAX_ORDER, pageblock_order + 1);

	VM_BUG_ON(!zone_is_initialized(zone));
	VM_BUG_ON_PAGE(page->flags & PAGE_FLAGS_CHECK_AT_PREP, page);

	VM_BUG_ON(migratetype == -1);
	if (likely(!is_migrate_isolate(migratetype)))
		__mod_zone_freepage_state(zone, 1 << order, migratetype);

	page_idx = pfn & ((1 << MAX_ORDER) - 1);

	VM_BUG_ON_PAGE(page_idx & ((1 << order) - 1), page);
	VM_BUG_ON_PAGE(bad_range(zone, page), page);

continue_merging:
	while (order < max_order - 1) {
		buddy_idx = __find_buddy_index(page_idx, order);
		buddy = page + (buddy_idx - page_idx);
		if (!page_is_buddy(page, buddy, order))
			goto done_merging;


		if (page_is_guard(buddy)) {
			clear_page_guard(zone, buddy, order, migratetype);
		} else {
			list_del(&buddy->lru);
			zone->free_area[order].nr_free--;
			rmv_page_order(buddy);
		}
		combined_idx = buddy_idx & page_idx;
		page = page + (combined_idx - page_idx);
		page_idx = combined_idx;
		order++;
	}
	if (max_order < MAX_ORDER) {


		if (unlikely(has_isolate_pageblock(zone))) {
			int buddy_mt;

			buddy_idx = __find_buddy_index(page_idx, order);
			buddy = page + (buddy_idx - page_idx);
			buddy_mt = get_pageblock_migratetype(buddy);

			if (migratetype != buddy_mt
					&& (is_migrate_isolate(migratetype) ||
						is_migrate_isolate(buddy_mt)))
				goto done_merging;
		}
		max_order++;
		goto continue_merging;
	}

done_merging:
	set_page_order(page, order);


	if ((order < MAX_ORDER-2) && pfn_valid_within(page_to_pfn(buddy))) {
		struct page *higher_page, *higher_buddy;
		combined_idx = buddy_idx & page_idx;
		higher_page = page + (combined_idx - page_idx);
		buddy_idx = __find_buddy_index(combined_idx, order + 1);
		higher_buddy = higher_page + (buddy_idx - combined_idx);
		if (page_is_buddy(higher_page, higher_buddy, order + 1)) {
			list_add_tail(&page->lru,
				&zone->free_area[order].free_list[migratetype]);
			goto out;
		}
	}

	list_add(&page->lru, &zone->free_area[order].free_list[migratetype]);
out:
	zone->free_area[order].nr_free++;
}
