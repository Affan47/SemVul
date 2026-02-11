range_end(u64 start, u64 len)
{
	if (start + len < start)
		return (u64)-1;
	return start + len;
}
