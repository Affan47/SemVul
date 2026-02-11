my_crashdump(char *buf, unsigned char *addr, int lines)
{

	int i;

	addr -= lines * 8;
	for(i = lines; i; i--, addr += 16)
	{
		int j;

		buf = maddrtoa(buf, addr);
		*buf++ = ':'; *buf++ = ' ';
		for(j = 0; j < 2; j++)
		{
			int k = 0;
			for(; k < 8; k++) {
				buf = mutoXa_0fix(buf, (unsigned int)addr[k] & 0xFF, 2);
				*buf++ = ' ';
			}
			*buf++ = ' ';
		}
		*buf++ = '\t';
		for(j = 0; j < 2; j++)
		{
			int k = 0;
			for(; k < 8; k++)
				*buf++ = isprint(addr[k]) ? addr[k] : (isspace_a(addr[k]) ? ' ' : '.');
			*buf++ = ' ';
		}
		*buf++ = '\n';
	}
	return buf;
}
