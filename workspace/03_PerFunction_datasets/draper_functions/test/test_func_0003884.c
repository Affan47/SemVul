from64tobits(void *out_, const char *in, int maxlen)


{
    int len = 0;
    register unsigned char digit1, digit2, digit3, digit4;
    unsigned char *out = (unsigned char *)out_;

    if (in[0] == '+' && in[1] == ' ')
	in += 2;
    if (*in == '\r')
	return(0);

    do {
	digit1 = in[0];
	if (DECODE64(digit1) == BAD)
	    return(-1);
	digit2 = in[1];
	if (DECODE64(digit2) == BAD)
	    return(-1);
	digit3 = in[2];
	if (digit3 != '=' && DECODE64(digit3) == BAD)
	    return(-1);
	digit4 = in[3];
	if (digit4 != '=' && DECODE64(digit4) == BAD)
	    return(-1);
	in += 4;
	++len;
	if (maxlen && len > maxlen)
	    return(-1);
	*out++ = (DECODE64(digit1) << 2) | (DECODE64(digit2) >> 4);
	if (digit3 != '=')
	{
	    ++len;
	    if (maxlen && len > maxlen)
	        return(-1);
	    *out++ = ((DECODE64(digit2) << 4) & 0xf0) | (DECODE64(digit3) >> 2);
	    if (digit4 != '=')
	    {
	        ++len;
		if (maxlen && len > maxlen)
		    return(-1);
		*out++ = ((DECODE64(digit3) << 6) & 0xc0) | DECODE64(digit4);
	    }
	}
    } while
	(*in && *in != '\r' && digit4 != '=');

    return (len);
}
