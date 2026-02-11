dump_page_badflags(struct page *page, const char *reason,
		unsigned long badflags)
{
	pr_emerg("page:%p count:%d mapcount:%d mapping:%p index:%#lx\n",
		  page, atomic_read(&page->_count), page_mapcount(page),
		  page->mapping, page->index);
	BUILD_BUG_ON(ARRAY_SIZE(pageflag_names) != __NR_PAGEFLAGS);
	dump_flags(page->flags, pageflag_names, ARRAY_SIZE(pageflag_names));
	if (reason)
		pr_alert("page dumped because: %s\n", reason);
	if (page->flags & badflags) {
		pr_alert("bad because of flags:\n");
		dump_flags(page->flags & badflags,
				pageflag_names, ARRAY_SIZE(pageflag_names));
	}
#ifdef CONFIG_MEMCG
	if (page->mem_cgroup)
		pr_alert("page->mem_cgroup:%p\n", page->mem_cgroup);
#endif
}
