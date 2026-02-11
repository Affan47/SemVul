swsusp_free(void)
{
	unsigned long fb_pfn, fr_pfn;

	if (!forbidden_pages_map || !free_pages_map)
		goto out;

	memory_bm_position_reset(forbidden_pages_map);
	memory_bm_position_reset(free_pages_map);

loop:
	fr_pfn = memory_bm_next_pfn(free_pages_map);
	fb_pfn = memory_bm_next_pfn(forbidden_pages_map);


	do {
		if (fb_pfn < fr_pfn)
			fb_pfn = memory_bm_next_pfn(forbidden_pages_map);
		if (fr_pfn < fb_pfn)
			fr_pfn = memory_bm_next_pfn(free_pages_map);
	} while (fb_pfn != fr_pfn);

	if (fr_pfn != BM_END_OF_MAP && pfn_valid(fr_pfn)) {
		struct page *page = pfn_to_page(fr_pfn);

		memory_bm_clear_current(forbidden_pages_map);
		memory_bm_clear_current(free_pages_map);
		__free_page(page);
		goto loop;
	}

out:
	nr_copy_pages = 0;
	nr_meta_pages = 0;
	restore_pblist = NULL;
	buffer = NULL;
	alloc_normal = 0;
	alloc_highmem = 0;
}
