memory_clear (void)
{
	mem_hardreset = 0;
	if (savestate_state == STATE_RESTORE)
		return;
	if (chipmemory)
		memset (chipmemory, 0, allocated_chipmem);
	if (bogomemory)
		memset (bogomemory, 0, allocated_bogomem);
	if (a3000lmemory)
		memset (a3000lmemory, 0, allocated_a3000lmem);
	if (a3000hmemory)
		memset (a3000hmemory, 0, allocated_a3000hmem);
	expansion_clear ();
}
