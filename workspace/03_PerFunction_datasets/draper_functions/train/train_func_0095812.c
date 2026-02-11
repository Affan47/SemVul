sgen_init_internal_allocator (void)
{
	int i, size;

	for (i = 0; i < INTERNAL_MEM_MAX; ++i)
		fixed_type_allocator_indexes [i] = -1;

	for (i = 0; i < NUM_ALLOCATORS; ++i) {
		allocator_block_sizes [i] = block_size (allocator_sizes [i]);
		mono_lock_free_allocator_init_size_class (&size_classes [i], allocator_sizes [i], allocator_block_sizes [i]);
		mono_lock_free_allocator_init_allocator (&allocators [i], &size_classes [i]);
	}

	for (size = mono_pagesize (); size <= LOCK_FREE_ALLOC_SB_MAX_SIZE; size <<= 1) {
		int max_size = LOCK_FREE_ALLOC_SB_USABLE_SIZE (size) / 2;


		g_assert (allocator_sizes [index_for_size (max_size)] == max_size);
	}
}
