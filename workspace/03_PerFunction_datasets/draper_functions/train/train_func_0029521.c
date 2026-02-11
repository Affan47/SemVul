_asn1_bmember_isset_bit(const void *data, unsigned int bit, size_t size)
{
#ifdef WORDS_BIGENDIAN
    if ((*(unsigned int *)data) & (1 << ((size * 8) - bit - 1)))
	return 1;
    return 0;
#else
    if ((*(unsigned int *)data) & (1 << bit))
	return 1;
    return 0;
#endif
}
