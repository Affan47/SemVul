from_base32(unsigned char *h, const tchar_t *str, unsigned num)
{
	unsigned b32chars = B32_LEN(num), i = 0, ch = 0, carry = 0;
	int shift = 11;

	do
	{
		unsigned tmp;
		if((tmp = str[ch] - 'A' ) < 26)
			carry |= tmp << shift;
		else if((tmp = str[ch] - 'a') < 26)
			carry |= tmp << shift;
		else if((tmp = str[ch] - '2') < 6)
			carry |= (tmp + 26) << shift;
		else
			return false;
		shift -= 5;
		if(shift < 0)
		{
			shift += 8;
			h[i++] = (unsigned char)(carry >> 8);
			carry <<= 8;
		}
	}
	while(++ch < b32chars)
		;
	h[i] = (unsigned char)(carry >> 8);
	return true;
}
