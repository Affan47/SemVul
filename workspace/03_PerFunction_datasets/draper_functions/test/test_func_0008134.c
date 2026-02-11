sgen_fragment_allocator_release (SgenFragmentAllocator *allocator)
{
	SgenFragment *last = allocator->region_head;
	if (!last)
		return;


	for (; last->next_in_order; last = last->next_in_order) ;

	last->next_in_order = fragment_freelist;
	fragment_freelist = allocator->region_head;
	allocator->alloc_head = allocator->region_head = NULL;
}
