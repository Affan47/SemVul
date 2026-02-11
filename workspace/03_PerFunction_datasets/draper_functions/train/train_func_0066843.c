round_pipe_size(unsigned int size)
{
	unsigned long nr_pages;

	if (size < pipe_min_size)
		size = pipe_min_size;

	nr_pages = (size + PAGE_SIZE - 1) >> PAGE_SHIFT;
	if (nr_pages == 0)
		return 0;

	return roundup_pow_of_two(nr_pages) << PAGE_SHIFT;
}
