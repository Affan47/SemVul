scroll_left(uint n)
{
	if (xofs > n) xofs -= n; else xofs = 0;
	return n;
}
