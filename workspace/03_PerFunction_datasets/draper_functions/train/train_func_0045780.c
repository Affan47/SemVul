index_to_offset(unsigned long idx, int size, unsigned long nr_args)
{
	if (idx < nr_args)
		return ARGS_START_OFFSET + __index_to_offset(idx);

	return 0UL - __index_to_offset(idx - nr_args + size);
}
