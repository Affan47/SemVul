prepare_to_space (char *to_space_bitmap, int space_bitmap_size)
{
	SgenFragment **previous, *frag;

	memset (to_space_bitmap, 0, space_bitmap_size);
	memset (age_alloc_buffers, 0, sizeof (age_alloc_buffers));

	previous = &collector_allocator.alloc_head;

	for (frag = *previous; frag; frag = *previous) {
		char *start = align_up (frag->fragment_next, SGEN_TO_SPACE_GRANULE_BITS);
		char *end = align_down (frag->fragment_end, SGEN_TO_SPACE_GRANULE_BITS);


		if ((end - start) < SGEN_MAX_NURSERY_WASTE) {
			sgen_clear_range (frag->fragment_next, frag->fragment_end);
			frag->fragment_next = frag->fragment_end = frag->fragment_start;
			*previous = frag->next;
			continue;
		}


		sgen_clear_range (start, end);

		if (start != frag->fragment_next)
			sgen_clear_range (frag->fragment_next, start);

		if (end != frag->fragment_end)
			sgen_clear_range (end, frag->fragment_end);

		frag->fragment_start = frag->fragment_next = start;
		frag->fragment_end = end;
		mark_bits_in_range (to_space_bitmap, start, end);
		previous = &frag->next;
	}
}
