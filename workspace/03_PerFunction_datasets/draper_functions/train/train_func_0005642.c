get_free_page(struct page **page)
{
	unsigned long flags;

	spin_lock_irqsave(&free_pages_lock, flags);
	if (list_empty(&scsiback_free_pages)) {
		spin_unlock_irqrestore(&free_pages_lock, flags);
		return gnttab_alloc_pages(1, page);
	}
	page[0] = list_first_entry(&scsiback_free_pages, struct page, lru);
	list_del(&page[0]->lru);
	free_pages_num--;
	spin_unlock_irqrestore(&free_pages_lock, flags);
	return 0;
}
