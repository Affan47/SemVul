crc32_addn(fingerprint_ty *p, unsigned char *s, size_t n)
{
    crc32_ty	    *c;
    unsigned long   x;
    unsigned char   newc;
    int		    i;

    c = (crc32_ty *)p;
    i = n;
    while (i >= 256)
    {
	if (!++c->len[1])
	    if (!++c->len[2])
		if (!++c->len[3])
		    if (!++c->len[4])
	       		if (!++c->len[5])
			    if (!++c->len[6])
			     	++c->len[7];
	i -= 256;
    }
    newc = i;
    if ((c->len[0] += newc) < newc)
	if (!++c->len[1])
    	    if (!++c->len[2])
       		if (!++c->len[3])
	  	    if (!++c->len[4])
	     		if (!++c->len[5])
			    if (!++c->len[6])
	    			++c->len[7];
    i = n;
    x = c->c;
    while (i--)
	x = crc_32_tab[(int)((x >> 24) ^ *s++) & 0xff] ^ (x << 8);
    c->c = x;
}
