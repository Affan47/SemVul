set_var_mtrr_range(struct var_mtrr_state *state, unsigned long base_pfn,
		   unsigned long size_pfn)
{
	unsigned long basek, sizek;
	unsigned long second_sizek = 0;

	if (state->reg >= num_var_ranges)
		return;

	basek = base_pfn << (PAGE_SHIFT - 10);
	sizek = size_pfn << (PAGE_SHIFT - 10);


	if ((basek <= 1024) ||
	    (state->range_startk + state->range_sizek == basek)) {
		unsigned long endk = basek + sizek;
		state->range_sizek = endk - state->range_startk;
		return;
	}

	if (state->range_sizek != 0)
		second_sizek = range_to_mtrr_with_hole(state, basek, sizek);


	state->range_startk = basek + second_sizek;
	state->range_sizek  = sizek - second_sizek;
}
