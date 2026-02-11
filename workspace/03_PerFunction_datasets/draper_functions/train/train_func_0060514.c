mono_lock_free_alloc (MonoLockFreeAllocator *heap)
{
	gpointer addr;

	for (;;) {

		addr = alloc_from_active_or_partial (heap);
		if (addr)
			break;

		addr = alloc_from_new_sb (heap);
		if (addr)
			break;
	}

	return addr;
}
