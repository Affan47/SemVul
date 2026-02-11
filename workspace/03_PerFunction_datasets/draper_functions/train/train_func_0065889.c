add_to_page_cache_lru(struct page *page, struct address_space *mapping,
				pgoff_t offset, gfp_t gfp_mask)
{
	void *shadow = NULL;
	int ret;

	__set_page_locked(page);
	ret = __add_to_page_cache_locked(page, mapping, offset,
					 gfp_mask, &shadow);
	if (unlikely(ret))
		__clear_page_locked(page);
	else {


		if (shadow && workingset_refault(shadow)) {
			SetPageActive(page);
			workingset_activation(page);
		} else
			ClearPageActive(page);
		lru_cache_add(page);
	}
	return ret;
}
