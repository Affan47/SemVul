parse_dotted_ip(p, vp)
    char *p;
    u_int32_t *vp;
{
    int n;
    u_int32_t v, b;
    char *endp, *p0 = p;

    v = 0;
    for (n = 3;; --n) {
	b = strtoul(p, &endp, 0);
	if (endp == p)
	    return 0;
	if (b > 255) {
	    if (n < 3)
		return 0;

	    *vp = b;
	    return endp - p0;
	}
	v |= b << (n * 8);
	p = endp;
	if (n == 0)
	    break;
	if (*p != '.')
	    return 0;
	++p;
    }
    *vp = v;
    return p - p0;
}
