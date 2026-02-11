buf_is_zero(const u8 *buf, size_t size)
{
	size_t i;
	for (i = 0; i < size; i++)
		if (buf[i])
			return 0;
	return 1;
}
