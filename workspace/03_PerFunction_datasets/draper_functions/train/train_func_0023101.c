_lllp_map_abstract_mask(bitstr_t *bitmask)
{
    	int i, bit;
	int num_bits = bit_size(bitmask);
	bitstr_t *newmask = NULL;
	newmask = (bitstr_t *) bit_alloc(num_bits);


	for (i = 0; i < num_bits; i++) {
		if (bit_test(bitmask,i)) {
			bit = BLOCK_MAP(i);
			if (bit < bit_size(newmask))
				bit_set(newmask, bit);
			else
				error("_lllp_map_abstract_mask: can't go from "
				      "%d -> %d since we only have %d bits",
				      i, bit, bit_size(newmask));
		}
	}
	return newmask;
}
