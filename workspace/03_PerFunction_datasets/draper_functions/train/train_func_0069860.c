FillRule(GB_PAINT *d, int set, int *value)
{
	if (set)
	{
		EXTRA(d)->fillRule = *value;
	}
	else
		*value = EXTRA(d)->fillRule;
}
