mtrr_check(unsigned long base, unsigned long size)
{
	if ((base & (PAGE_SIZE - 1)) || (size & (PAGE_SIZE - 1))) {
		pr_warning("mtrr: size and base must be multiples of 4 kiB\n");
		pr_debug("mtrr: size: 0x%lx  base: 0x%lx\n", size, base);
		dump_stack();
		return -1;
	}
	return 0;
}
