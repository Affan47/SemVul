___alloc_bootmem_node(pg_data_t *pgdat, unsigned long size,
				    unsigned long align, unsigned long goal,
				    unsigned long limit)
{
	void *ptr;

	ptr = ___alloc_bootmem_node_nopanic(pgdat, size, align, goal, limit);
	if (ptr)
		return ptr;

	printk(KERN_ALERT "bootmem alloc of %lu bytes failed!\n", size);
	panic("Out of memory");
	return NULL;
}
