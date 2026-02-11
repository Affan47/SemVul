rotate_num(int cur, int off, int first, int last)
{
	if (cur+off > last)
		return first + (cur+off-last-1) % ((last+1)-first);
	if (cur+off < first)
		return last - (first-(cur+off)-1) % ((last+1)-first);
	return cur+off;
}
