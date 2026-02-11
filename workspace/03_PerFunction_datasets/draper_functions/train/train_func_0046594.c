lru_add_page_tail(struct page *page, struct page *page_tail,
		       struct lruvec *lruvec, struct list_head *list)
{
	const int file = 0;

	VM_BUG_ON_PAGE(!PageHead(page), page);
	VM_BUG_ON_PAGE(PageCompound(page_tail), page);
	VM_BUG_ON_PAGE(PageLRU(page_tail), page);
	VM_BUG_ON(NR_CPUS != 1 &&
		  !spin_is_locked(&lruvec_zone(lruvec)->lru_lock));

	if (!list)
		SetPageLRU(page_tail);

	if (likely(PageLRU(page)))
		list_add_tail(&page_tail->lru, &page->lru);
	else if (list) {

		get_page(page_tail);
		list_add_tail(&page_tail->lru, list);
	} else {
		struct list_head *list_head;


		add_page_to_lru_list(page_tail, lruvec, page_lru(page_tail));
		list_head = page_tail->lru.prev;
		list_move_tail(&page_tail->lru, list_head);
	}

	if (!PageUnevictable(page))
		update_page_reclaim_stat(lruvec, file, PageActive(page_tail));
}
