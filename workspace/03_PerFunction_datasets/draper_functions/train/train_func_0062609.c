page_anon_vma(struct page *page)
{
	unsigned long mapping;

	page = compound_head(page);
	mapping = (unsigned long)page->mapping;
	if ((mapping & PAGE_MAPPING_FLAGS) != PAGE_MAPPING_ANON)
		return NULL;
	return __page_rmapping(page);
}
