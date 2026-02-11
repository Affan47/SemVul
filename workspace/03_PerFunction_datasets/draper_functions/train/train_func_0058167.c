omapi_td_strcasecmp (omapi_typed_data_t *s1, const char *s2)
{
	unsigned len, slen;
	int rv;


	if (s1 -> type != omapi_datatype_data &&
	    s1 -> type != omapi_datatype_string)
		return -1;

	slen = strlen (s2);
	if (slen > s1 -> u.buffer.len)
		len = s1 -> u.buffer.len;
	else
		len = slen;
	rv = casecmp (s1 -> u.buffer.value, s2, len);
	if (rv)
		return rv;
	if (s1 -> u.buffer.len > slen)
		return 1;
	else if (s1 -> u.buffer.len < slen)
		return -1;
	return 0;
}
