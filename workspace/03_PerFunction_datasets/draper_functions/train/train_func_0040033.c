__alloc_memory_core_early(int nid, u64 size, u64 align,
					u64 goal, u64 limit)
{
	void *ptr;
	u64 addr;
	ulong flags = choose_memblock_flags();

	if (limit > memblock.current_limit)
		limit = memblock.current_limit;

again:
	addr = memblock_find_in_range_node(size, align, goal, limit, nid,
					   flags);
	if (!addr && (flags & MEMBLOCK_MIRROR)) {
		flags &= ~MEMBLOCK_MIRROR;
		pr_warn("Could not allocate %pap bytes of mirrored memory\n",
			&size);
		goto again;
	}
	if (!addr)
		return NULL;

	if (memblock_reserve(addr, size))
		return NULL;

	ptr = phys_to_virt(addr);
	memset(ptr, 0, size);


	kmemleak_alloc(ptr, size, 0, 0);
	return ptr;
}
