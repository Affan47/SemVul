calc_dec_size(int nr_bits, int is_signed)
{
	int r;
	if (is_signed) --nr_bits;
	r = (nr_bits * 146L + 484) / 485;
	if (is_signed) ++r;
	return r;
}
