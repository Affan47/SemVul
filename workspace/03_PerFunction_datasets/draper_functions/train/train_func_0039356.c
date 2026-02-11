allocate_signal_page(struct file *devkfd, struct kfd_process *p)
{
	void *backing_store;
	struct signal_page *page;

	page = kzalloc(SIGNAL_PAGE_SIZE, GFP_KERNEL);
	if (!page)
		goto fail_alloc_signal_page;

	page->free_slots = SLOTS_PER_PAGE;

	backing_store = (void *) __get_free_pages(GFP_KERNEL | __GFP_ZERO,
					get_order(KFD_SIGNAL_EVENT_LIMIT * 8));
	if (!backing_store)
		goto fail_alloc_signal_store;


	memset(backing_store, (uint8_t) UNSIGNALED_EVENT_SLOT,
		KFD_SIGNAL_EVENT_LIMIT * 8);

	page->kernel_address = backing_store;

	if (list_empty(&p->signal_event_pages))
		page->page_index = 0;
	else
		page->page_index = list_tail_entry(&p->signal_event_pages,
						   struct signal_page,
						   event_pages)->page_index + 1;

	pr_debug("allocated new event signal page at %p, for process %p\n",
			page, p);
	pr_debug("page index is %d\n", page->page_index);

	list_add(&page->event_pages, &p->signal_event_pages);

	return true;

fail_alloc_signal_store:
	kfree(page);
fail_alloc_signal_page:
	return false;
}
