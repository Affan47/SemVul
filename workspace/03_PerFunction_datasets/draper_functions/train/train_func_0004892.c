uinttobase64(char *buf, uint64_t v, int64_t count)
{
	buf[count] = '\0';

	while (count > 0)
	{
		buf[--count] = ub64_alphabet[v & 63];
		v >>= 6;
	}

	return buf;
}
