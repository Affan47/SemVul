add_ptr(char *p)
{
    if (ap == ap_end) {
	unsigned int size = CHUNK;
	char **nap;
	while ((ap-ap_start) * sizeof(char *) >= size)
	    size = size * 2;
	if (!(nap = malloc(size)))
	    no_space();
	if (ap > ap_start)
	    memcpy(nap, ap_start, (ap-ap_start) * sizeof(char *));
	ap = nap + (ap - ap_start);
	ap_start = nap;
	ap_end = nap + size/sizeof(char *); }
    *ap++ = p;
}
