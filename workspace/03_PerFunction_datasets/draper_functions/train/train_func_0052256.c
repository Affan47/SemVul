lfsr_reset(struct fio_lfsr *fl, unsigned long seed)
{
	uint64_t bitmask = (fl->cached_bit << 1) - 1;

	fl->num_vals = 0;
	fl->last_val = seed & bitmask;


	if (fl->last_val == bitmask)
		return 1;

	return 0;
}
