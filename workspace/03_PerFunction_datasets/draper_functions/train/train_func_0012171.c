clear_extent_buffer_uptodate(struct extent_buffer *eb)
{
	unsigned long i;
	struct page *page;
	unsigned long num_pages;

	clear_bit(EXTENT_BUFFER_UPTODATE, &eb->bflags);
	num_pages = num_extent_pages(eb->start, eb->len);
	for (i = 0; i < num_pages; i++) {
		page = eb->pages[i];
		if (page)
			ClearPageUptodate(page);
	}
	return 0;
}
