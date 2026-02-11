page_table_new(void)
{
	static const struct page_table zero_page_table;
	struct page_table *tab;

	g_assert((size_t)-1 == (uint32)-1);
	g_assert(compat_pagesize() == (1 << PAGE_BITSHIFT));

	tab = xpmalloc(sizeof *tab);
	g_assert(tab);
	*tab = zero_page_table;
	return tab;
}
