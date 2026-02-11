range(low,item,hi)
int low, item, hi;
{
	if (item < low) return low;
	if (item > hi) return hi;
	return item;
}
