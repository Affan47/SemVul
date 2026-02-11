not_in_range(const void* mem_from, unsigned long mem_len,
				const void* lock_from, unsigned long lock_len)
{
	return lock_from + lock_len <= mem_from ||
		mem_from + mem_len <= lock_from;
}
