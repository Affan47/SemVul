min_odd(unsigned int x, unsigned int y)
{
	unsigned int val = min(x, y);

	return val % 2 ? val : val - 1;
}
