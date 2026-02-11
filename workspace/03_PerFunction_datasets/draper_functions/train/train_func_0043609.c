get_bits_up(size_t u)
{
	unsigned i = 0;
	while ((1U << i) < u)
		i++;
	return i;
}
