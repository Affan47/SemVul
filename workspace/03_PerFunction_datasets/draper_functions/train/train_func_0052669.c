add_nursery_frag (SgenFragmentAllocator *allocator, size_t frag_size, char* frag_start, char* frag_end)
{
	SGEN_LOG (4, "Found empty fragment: %p-%p, size: %zd", frag_start, frag_end, frag_size);
	binary_protocol_empty (frag_start, frag_size);

	if (frag_size >= SGEN_MAX_NURSERY_WASTE) {

		if (sgen_get_nursery_clear_policy () == CLEAR_AT_GC)
			memset (frag_start, 0, frag_size);
		else if (sgen_get_nursery_clear_policy () == CLEAR_AT_TLAB_CREATION_DEBUG)
			memset (frag_start, 0xff, frag_size);

#ifdef NALLOC_DEBUG


#endif
		sgen_fragment_allocator_add (allocator, frag_start, frag_end);
		fragment_total += frag_size;
	} else {

		sgen_clear_range (frag_start, frag_end);
		HEAVY_STAT (stat_wasted_bytes_small_areas += frag_size);
	}
}
