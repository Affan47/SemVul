entry_getlen(unsigned char **buf)
{
	ber_len_t len;
	int i;

	len = *(*buf)++;
	if (len <= 0x7f)
		return len;
	i = len & 0x7f;
	len = 0;
	for (;i > 0; i--) {
		len <<= 8;
		len |= *(*buf)++;
	}
	return len;
}
