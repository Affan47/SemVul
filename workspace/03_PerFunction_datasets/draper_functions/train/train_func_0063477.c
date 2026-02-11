omapi_data_string_cmp (omapi_data_string_t *s1, omapi_data_string_t *s2)
{
	unsigned len;
	int rv;

	if (s1 -> len > s2 -> len)
		len = s2 -> len;
	else
		len = s1 -> len;
	rv = memcmp (s1 -> value, s2 -> value, len);
	if (rv)
		return rv;
	if (s1 -> len > s2 -> len)
		return 1;
	else if (s1 -> len < s2 -> len)
		return -1;
	return 0;
}
