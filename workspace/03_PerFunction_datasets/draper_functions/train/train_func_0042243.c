sgen_fragment_allocator_serial_range_alloc (SgenFragmentAllocator *allocator, size_t desired_size, size_t minimum_size, size_t *out_alloc_size)
{
	SgenFragment *frag, **previous, *min_frag = NULL, **prev_min_frag = NULL;
	size_t current_minimum = minimum_size;

#ifdef NALLOC_DEBUG
	InterlockedIncrement (&alloc_count);
#endif

	previous = &allocator->alloc_head;

	for (frag = *previous; frag; frag = *previous) {
		size_t frag_size = frag->fragment_end - frag->fragment_next;

		HEAVY_STAT (InterlockedIncrement (&stat_alloc_range_iterations));

		if (desired_size <= frag_size) {
			void *p;
			*out_alloc_size = desired_size;

			p = serial_alloc_from_fragment (previous, frag, desired_size);
#ifdef NALLOC_DEBUG
			add_alloc_record (p, desired_size, RANGE_ALLOC);
#endif
			return p;
		}
		if (current_minimum <= frag_size) {
			min_frag = frag;
			prev_min_frag = previous;
			current_minimum = frag_size;
		}
		previous = &frag->next;
	}

	if (min_frag) {
		void *p;
		size_t frag_size = min_frag->fragment_end - min_frag->fragment_next;
		*out_alloc_size = frag_size;

		p = serial_alloc_from_fragment (prev_min_frag, min_frag, frag_size);

#ifdef NALLOC_DEBUG
		add_alloc_record (p, frag_size, RANGE_ALLOC);
#endif
		return p;
	}

	return NULL;
}
