percent_decode(char *buf)
{
    unsigned char *in = (unsigned char *) buf;
    unsigned char *out = (unsigned char *) buf;
    unsigned int val;

    if (!buf) {
	return;
    }

    while(*in) {
	if (*in == '%' && isxdigit(*(in+1)) && isxdigit(*(in+2))) {
	    sscanf((char *) in+1, "%2x", &val);
	    *out++ = (unsigned char) val;
	    in += 3;
	    continue;
	}
	*out++ = *in++;
    }

    *out = 0;
}
