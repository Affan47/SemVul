xen_hyper_x86_memory_size(void)
{
	ulong vaddr;

	if (machdep->memsize) {
		return machdep->memsize;
	}
	vaddr = symbol_value("total_pages");
	if (!readmem(vaddr, KVADDR, &xht->total_pages, sizeof(xht->total_pages),
		"total_pages", RETURN_ON_ERROR)) {
		error(WARNING, "cannot read total_pages.\n");
	}
	xht->sys_pages = xht->total_pages;
	machdep->memsize = (uint64_t)(xht->sys_pages) * (uint64_t)(machdep->pagesize);
	return machdep->memsize;
}
