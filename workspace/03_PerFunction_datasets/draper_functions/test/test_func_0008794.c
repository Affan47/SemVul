convert_shorts(unsigned char *buf, short *Numbers, unsigned count)
{
    unsigned i;
    for (i = 0; i < count; i++) {
	if (Numbers[i] == ABSENT_NUMERIC) {
	    buf[2 * i] = buf[2 * i + 1] = 0377;
	} else if (Numbers[i] == CANCELLED_NUMERIC) {
	    buf[2 * i] = 0376;
	    buf[2 * i + 1] = 0377;
	} else {
	    LITTLE_ENDIAN(buf + 2 * i, Numbers[i]);
	    TRACE_OUT(("put Numbers[%d]=%d", i, Numbers[i]));
	}
    }
}
