dm_bitset_create(struct dm_pool *mem, unsigned num_bits)
{
	unsigned n = (num_bits / DM_BITS_PER_INT) + 2;
	size_t size = sizeof(int) * n;
	dm_bitset_t bs;

	if (mem)
		bs = dm_pool_zalloc(mem, size);
	else
		bs = dm_zalloc(size);

	if (!bs)
		return NULL;

	*bs = num_bits;

	return bs;
}
