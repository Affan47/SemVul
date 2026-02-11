sgen_free_internal (void *addr, int type)
{
	int index;

	if (!addr)
		return;

	index = fixed_type_allocator_indexes [type];
	g_assert (index >= 0 && index < NUM_ALLOCATORS);

	mono_lock_free_free (addr);

	if (MONO_GC_INTERNAL_DEALLOC_ENABLED ()) {
		int size G_GNUC_UNUSED = allocator_sizes [index];
		MONO_GC_INTERNAL_DEALLOC ((mword)addr, size, type);
	}
}
