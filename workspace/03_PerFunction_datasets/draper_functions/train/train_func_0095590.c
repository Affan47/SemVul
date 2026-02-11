fscache_mark_pages_cached(struct fscache_retrieval *op,
			       struct pagevec *pagevec)
{
	unsigned long loop;

	for (loop = 0; loop < pagevec->nr; loop++)
		fscache_mark_page_cached(op, pagevec->pages[loop]);

	pagevec_reinit(pagevec);
}
