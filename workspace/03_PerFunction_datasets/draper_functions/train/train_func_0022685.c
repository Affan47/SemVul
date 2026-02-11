aggregate_64bit(uint64_t * dest, uint64_t val)
{
	if (((*dest) + val) < (*dest))
		(*dest) = 0xffffffffffffffffULL;
	else
		(*dest) = (*dest) + val;
}
