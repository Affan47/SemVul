halloc(size_t size)
#endif
{
	void *p;
	size_t allocated;

	if (0 == size)
		return NULL;

	if G_UNLIKELY(0 == xpmalloc_threshold)
		halloc_init(TRUE);

	hstats.allocations++;

	if (size < xpmalloc_threshold) {
		p = xpmalloc(size);
		allocated = xallocated(p);
		hstats.alloc_via_xpmalloc++;
	} else {
		int inserted;


		allocated = round_pagesize(size);
		g_assert(allocated >= size);

		p = vmm_alloc(allocated);
		inserted = page_insert(p, allocated);
		g_assert(inserted);
		hstats.alloc_via_vmm++;
	}
	hstats.memory += allocated;
	hstats.blocks++;
	return p;
}
