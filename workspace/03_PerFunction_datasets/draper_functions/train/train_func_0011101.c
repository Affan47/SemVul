alloc_nursery (void)
{
	GCMemSection *section;
	char *data;
	size_t scan_starts;
	size_t alloc_size;

	if (nursery_section)
		return;
	SGEN_LOG (2, "Allocating nursery size: %zu", (size_t)sgen_nursery_size);


	section = (GCMemSection *)sgen_alloc_internal (INTERNAL_MEM_SECTION);

	alloc_size = sgen_nursery_size;


	g_assert (sgen_memgov_try_alloc_space (alloc_size, SPACE_NURSERY));

	data = (char *)major_collector.alloc_heap (alloc_size, alloc_size, DEFAULT_NURSERY_BITS);
	sgen_update_heap_boundaries ((mword)data, (mword)(data + sgen_nursery_size));
	SGEN_LOG (4, "Expanding nursery size (%p-%p): %lu, total: %lu", data, data + alloc_size, (unsigned long)sgen_nursery_size, (unsigned long)sgen_gc_get_total_heap_allocation ());
	section->data = section->next_data = data;
	section->size = alloc_size;
	section->end_data = data + sgen_nursery_size;
	scan_starts = (alloc_size + SCAN_START_SIZE - 1) / SCAN_START_SIZE;
	section->scan_starts = (char **)sgen_alloc_internal_dynamic (sizeof (char*) * scan_starts, INTERNAL_MEM_SCAN_STARTS, TRUE);
	section->num_scan_start = scan_starts;

	nursery_section = section;

	sgen_nursery_allocator_set_nursery_bounds (data, data + sgen_nursery_size);
}
