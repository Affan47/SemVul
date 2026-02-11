khugepaged_do_scan(void)
{
	struct page *hpage = NULL;
	unsigned int progress = 0, pass_through_head = 0;
	unsigned int pages = khugepaged_pages_to_scan;
	bool wait = true;

	barrier();

	while (progress < pages) {
		if (!khugepaged_prealloc_page(&hpage, &wait))
			break;

		cond_resched();

		if (unlikely(kthread_should_stop() || try_to_freeze()))
			break;

		spin_lock(&khugepaged_mm_lock);
		if (!khugepaged_scan.mm_slot)
			pass_through_head++;
		if (khugepaged_has_work() &&
		    pass_through_head < 2)
			progress += khugepaged_scan_mm_slot(pages - progress,
							    &hpage);
		else
			progress = pages;
		spin_unlock(&khugepaged_mm_lock);
	}

	if (!IS_ERR_OR_NULL(hpage))
		put_page(hpage);
}
