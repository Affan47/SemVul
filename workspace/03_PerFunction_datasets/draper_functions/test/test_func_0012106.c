sgen_alloc_internal (int type)
{
	int index, size;
	void *p;

	index = fixed_type_allocator_indexes [type];
	g_assert (index >= 0 && index < NUM_ALLOCATORS);

#ifdef HEAVY_STATISTICS
	++ allocator_sizes_stats [index];
#endif

	size = allocator_sizes [index];

	p = mono_lock_free_alloc (&allocators [index]);
	memset (p, 0, size);

	return p;
}
