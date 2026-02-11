do_one_pass(u64 pattern, phys_addr_t start, phys_addr_t end)
{
	u64 i;
	phys_addr_t this_start, this_end;

	for_each_free_mem_range(i, NUMA_NO_NODE, MEMBLOCK_NONE, &this_start,
				&this_end, NULL) {
		this_start = clamp(this_start, start, end);
		this_end = clamp(this_end, start, end);
		if (this_start < this_end) {
			pr_info("  %pa - %pa pattern %016llx\n",
				&this_start, &this_end, cpu_to_be64(pattern));
			memtest(pattern, this_start, this_end - this_start);
		}
	}
}
