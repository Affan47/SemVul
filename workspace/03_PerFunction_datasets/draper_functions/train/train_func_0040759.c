page_evictable(struct page *page)
{
	return !mapping_unevictable(page_mapping(page)) && !PageMlocked(page);
}
