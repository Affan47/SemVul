smbb_hw_lookup(unsigned int val, int (*fn)(unsigned int))
{
	unsigned int widx;
	unsigned int sel;

	for (widx = sel = 0; (*fn)(widx) <= val; ++widx)
		sel = widx;

	return sel;
}
