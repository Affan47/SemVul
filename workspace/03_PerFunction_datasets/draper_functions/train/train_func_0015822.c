in_range(int val, int lo, int hi)
{
	return val < 0 || (val <= hi && val >= lo);
}
