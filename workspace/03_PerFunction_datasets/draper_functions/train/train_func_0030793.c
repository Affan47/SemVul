CLASSIFY_string_to_priority(const char *s, unsigned int *p)
{
	unsigned int i, j;

	if (sscanf(s, "%x:%x", &i, &j) != 2)
		return 1;

	*p = TC_H_MAKE(i<<16, j);
	return 0;
}
