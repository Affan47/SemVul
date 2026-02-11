lookup_swap_cache(swp_entry_t entry)
{
	struct page *page;

	page = find_get_page(swap_address_space(entry), entry.val);

	if (page) {
		INC_CACHE_INFO(find_success);
		if (TestClearPageReadahead(page))
			atomic_inc(&swapin_readahead_hits);
	}

	INC_CACHE_INFO(find_total);
	return page;
}
