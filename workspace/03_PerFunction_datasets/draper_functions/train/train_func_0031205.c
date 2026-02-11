sgen_nursery_alloc (size_t size)
{
	SGEN_LOG (4, "Searching nursery for size: %zd", size);
	size = SGEN_ALIGN_UP (size);

	HEAVY_STAT (InterlockedIncrement (&stat_nursery_alloc_requests));

	return sgen_fragment_allocator_par_alloc (&mutator_allocator, size);
}
