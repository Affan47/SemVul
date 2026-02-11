rvfree(void *mem, unsigned long size)
{
	unsigned long adr;

	if (!mem)
		return;

	size = PAGE_ALIGN(size);

	adr = (unsigned long) mem;
	while ((long)size > 0) {
		ClearPageReserved(vmalloc_to_page((void *)adr));
		adr += PAGE_SIZE;
		size -= PAGE_SIZE;
	}
	vfree(mem);
}
