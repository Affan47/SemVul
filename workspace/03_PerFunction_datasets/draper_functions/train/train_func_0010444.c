min_bytes_needed(unsigned long val)
{
	int c = 0;
	int i;

	for (i = (sizeof val * 8) - 1; i >= 0; --i, ++c)
		if (val & (1UL << i))
			break;
	c = (sizeof val * 8) - c;
	if (!c || (c % 8))
		c = (c + 8) / 8;
	else
		c /= 8;
	return c;
}
