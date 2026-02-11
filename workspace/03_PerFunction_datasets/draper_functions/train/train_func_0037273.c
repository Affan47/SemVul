next_power(unsigned n, unsigned min)
{
	return roundup_pow_of_two(max(n, min));
}
