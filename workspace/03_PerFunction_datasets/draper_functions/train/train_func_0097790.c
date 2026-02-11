r600_mip_minify(unsigned size, unsigned level)
{
	unsigned val;

	val = max(1U, size >> level);
	if (level > 0)
		val = roundup_pow_of_two(val);
	return val;
}
