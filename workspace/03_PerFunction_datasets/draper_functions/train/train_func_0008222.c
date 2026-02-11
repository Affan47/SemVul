string_hash(const void *s)
{
	const signed char *p = s;
	unsigned hash = 0;
	int c;

	while ('\0' != (c = *p++))
		hash = (hash << 5) - hash + c;

	return hash;
}
