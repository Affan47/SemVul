__free_pages_memory(unsigned long start, unsigned long end)
{
	int order;

	while (start < end) {
		order = min(MAX_ORDER - 1UL, __ffs(start));

		while (start + (1UL << order) > end)
			order--;

		__free_pages_bootmem(pfn_to_page(start), start, order);

		start += (1UL << order);
	}
}
