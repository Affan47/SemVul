dns_copylabel(void *dst, const void *src, const void *buf)
{
    uint8_t *q = dst;
    const uint8_t *p = src;
    unsigned int c0, c1;

    while (1) {
	c0 = p[0];
        if (c0 >= 0xc0) {

	    c1 = p[1];
	    p = (const uint8_t *)buf + ((c0 - 0xc0) << 8) + c1;
	} else if (c0) {
	    c0++;
	    memcpy(q, p, c0);
	    p += c0;
	    q += c0;
	} else {
	    *q++ = 0;
	    return q;
	}
    }
}
