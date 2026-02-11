fb_deferred_io_set_page_dirty(struct page *page)
{
	if (!PageDirty(page))
		SetPageDirty(page);
	return 0;
}
