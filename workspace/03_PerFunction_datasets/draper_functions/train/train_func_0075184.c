ct_memcmp(const void *p1, const void *p2, size_t len)
{
    const unsigned char *s1 = p1, *s2 = p2;
    size_t i;
    int r = 0;

    for (i = 0; i < len; i++)
	r |= (s1[i] ^ s2[i]);
    return !!r;
}
