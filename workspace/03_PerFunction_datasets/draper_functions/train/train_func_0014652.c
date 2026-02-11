aggregate_16bit(uint32_t * dest, uint32_t val)
{
	if ((((*dest) + val) < (*dest))
	    || ((*dest) + val) > 0xffff)
		(*dest) = 0xffff;
	else
		(*dest) = (*dest) + val;
}
