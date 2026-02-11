state_name(enum lock_usage_bit bit)
{
	return (bit & 1) ? state_rnames[bit >> 2] : state_names[bit >> 2];
}
