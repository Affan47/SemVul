string_hash(const void *key)
{
	unsigned long hash;
	const char *str;

	hash = 0;
	str  = key;

	while (*str)
		hash += 31 * hash + *str++;

	return hash;
}
