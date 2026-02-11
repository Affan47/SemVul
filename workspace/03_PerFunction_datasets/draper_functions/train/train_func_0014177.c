cp932_char2int(const unsigned char* in, unsigned int* out)
{
    if (((0x81 <= in[0] && in[0] <= 0x9f)
		|| (0xe0 <= in[0] && in[0] <= 0xf0))
	    && ((0x40 <= in[1] && in[1] <= 0x7e)
		|| (0x80 <= in[1] && in[1] <= 0xfc)))
    {
	if (out)
	    *out = (unsigned int)in[0] << 8 | (unsigned int)in[1];
	return 2;
    }
    else
    {
	if (out)
	    *out = in[0];
	return 1;
    }
}
