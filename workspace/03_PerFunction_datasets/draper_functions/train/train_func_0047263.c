icmp(const void *va, const void *vb)
{
    const int	    *a;
    const int	    *b;

    a = (const int *)va;
    b = (const int *)vb;
    if (*a == *b)
	return 0;
    if (*a < *b)
	return -1;
    return 1;
}
