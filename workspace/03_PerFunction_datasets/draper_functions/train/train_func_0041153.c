sgen_alloc_os_memory_aligned (size_t size, mword alignment, SgenAllocFlags flags, const char *assert_description)
{
	void *ptr;

	g_assert (!(flags & ~(SGEN_ALLOC_HEAP | SGEN_ALLOC_ACTIVATE)));

	ptr = mono_valloc_aligned (size, alignment, prot_flags_for_activate (flags & SGEN_ALLOC_ACTIVATE));
	sgen_assert_memory_alloc (ptr, size, assert_description);
	if (ptr) {
		SGEN_ATOMIC_ADD_P (total_alloc, size);
		total_alloc_max = MAX (total_alloc_max, total_alloc);
	}
	return ptr;
}
