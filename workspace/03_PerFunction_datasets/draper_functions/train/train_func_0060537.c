sgen_free_internal_dynamic (void *addr, size_t size, int type)
{
	if (!addr)
		return;

	if (size > allocator_sizes [NUM_ALLOCATORS - 1])
		sgen_free_os_memory (addr, size, SGEN_ALLOC_INTERNAL);
	else
		mono_lock_free_free (addr);

	MONO_GC_INTERNAL_DEALLOC ((mword)addr, size, type);
}
