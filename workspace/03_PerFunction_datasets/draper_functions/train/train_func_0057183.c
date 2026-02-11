isns_bitvector_clear_bit(isns_bitvector_t *bv, unsigned int bit)
{
	uint32_t	*pos, oldval, mask;

	pos = __isns_bitvector_find_word(bv, bit);
	if (pos == NULL)
		return 0;

	mask = 1 << (bit % 32);
	oldval = *pos;
	*pos &= ~mask;

	__isns_bitvector_compact(bv);
	return !!(oldval & mask);
}
