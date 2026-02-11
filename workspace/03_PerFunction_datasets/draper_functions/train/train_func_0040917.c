__set_page_owner(struct page *page, unsigned int order, gfp_t gfp_mask)
{
	struct page_ext *page_ext = lookup_page_ext(page);

	struct stack_trace trace = {
		.nr_entries = 0,
		.max_entries = ARRAY_SIZE(page_ext->trace_entries),
		.entries = &page_ext->trace_entries[0],
		.skip = 3,
	};

	if (unlikely(!page_ext))
		return;

	save_stack_trace(&trace);

	page_ext->order = order;
	page_ext->gfp_mask = gfp_mask;
	page_ext->nr_entries = trace.nr_entries;

	__set_bit(PAGE_EXT_OWNER, &page_ext->flags);
}
