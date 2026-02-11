soft_offline_page(struct page *page, int flags)
{
	int ret;
	unsigned long pfn = page_to_pfn(page);
	struct page *hpage = compound_head(page);

	if (PageHWPoison(page)) {
		pr_info("soft offline: %#lx page already poisoned\n", pfn);
		if (flags & MF_COUNT_INCREASED)
			put_hwpoison_page(page);
		return -EBUSY;
	}
	if (!PageHuge(page) && PageTransHuge(hpage)) {
		if (PageAnon(hpage) && unlikely(split_huge_page(hpage))) {
			pr_info("soft offline: %#lx: failed to split THP\n",
				pfn);
			if (flags & MF_COUNT_INCREASED)
				put_hwpoison_page(page);
			return -EBUSY;
		}
	}

	get_online_mems();

	ret = get_any_page(page, pfn, flags);
	put_online_mems();
	if (ret > 0) {
		if (PageHuge(page))
			ret = soft_offline_huge_page(page, flags);
		else
			ret = __soft_offline_page(page, flags);
	} else if (ret == 0) {
		if (PageHuge(page)) {
			set_page_hwpoison_huge_page(hpage);
			if (!dequeue_hwpoisoned_huge_page(hpage))
				num_poisoned_pages_add(1 << compound_order(hpage));
		} else {
			if (!TestSetPageHWPoison(page))
				num_poisoned_pages_inc();
		}
	}
	return ret;
}
