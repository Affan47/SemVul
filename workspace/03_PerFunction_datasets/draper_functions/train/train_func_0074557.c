kgdb_flush_swbreak_addr(unsigned long addr)
{
	if (!CACHE_FLUSH_IS_SAFE)
		return;

	if (current->mm) {
		int i;

		for (i = 0; i < VMACACHE_SIZE; i++) {
			if (!current->vmacache[i])
				continue;
			flush_cache_range(current->vmacache[i],
					  addr, addr + BREAK_INSTR_SIZE);
		}
	}


	flush_icache_range(addr, addr + BREAK_INSTR_SIZE);
}
