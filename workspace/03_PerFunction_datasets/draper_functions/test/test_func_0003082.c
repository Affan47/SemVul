put_dec_8bit_2fix(char *buf, unsigned q)
{
	unsigned r;

	r      = (q * 0xcd) >> 11;
	*buf++ = (q - 10 * r) + '0';

	q      = (r * 0xd) >> 7;
	*buf++ = (r - 10 * q)  + '0';

	if(unlikely(q))
		*buf++ = q + '0';

	return buf;
}
