save_all_pages(GSList *prefs_pages)
{
	GSList *cur;

	for (cur = prefs_pages; cur != NULL; cur = g_slist_next(cur)) {
		PrefsPage *page = (PrefsPage *) cur->data;

		if (page->page_open) {
			page->save_page(page);
		}
	}
}
