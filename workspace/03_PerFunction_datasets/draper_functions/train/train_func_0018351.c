find_right(const char *s, int len, int start,
			   const char *x, int x_len)
{
    if (start >= len)
	start = len - x_len;
    if (x_len == 0)
	return start >= 0 ? start : -1;
    for (int i = start; i >= 0; --i)
	if (memcmp(s + i, x, x_len) == 0)
	    return i;
    return -1;
}
