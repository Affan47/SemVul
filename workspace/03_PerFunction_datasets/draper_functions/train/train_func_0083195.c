r5_hash(char *str)
{
	unsigned long hash = 0;
	int c;

	c = *str;
	while (c) {
		hash = (hash + (c << 4) + (c >> 4)) * 11;
		c = *++str;
	}
	return (unsigned int)(hash & ((1 << DYNAMIC_DEBUG_HASH_BITS) - 1));
}
