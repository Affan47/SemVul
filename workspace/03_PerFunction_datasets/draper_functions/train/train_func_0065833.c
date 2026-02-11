new_filter_host(enum filtertype type, const char *matchstr)
{
    struct filter *f;
    char *mask;
    int i;

    if (!(f = __new_filter(type))) return f;

    f->u.addrs.addrstr = strdup(matchstr);
    if((mask = strchr(f->u.addrs.addrstr, '/'))) {
	*mask++ = 0;
	if(!str_to_int(mask, &i)) {

	    uint32_t l = 0xffffffff;
	    if(i < 0 || i > 32) {
		fprintf(stderr, "can't parse netmask \"%s\"\n",
			mask);
		return NULL;
	    }
	    if(!i)
		l = 0;
	    else {
		i = 32 - i;
		l >>= i; l <<= i;
	    }
	    f->u.addrs.mask.s_addr = htonl(l);
	} else {

	    if(!inet_aton(mask, &f->u.addrs.mask)) {
		fprintf(stderr, "can't parse netmask \"%s\"\n",
			mask);
		return NULL;
	    }
	}
	f->u.addrs.maskstr = strdup(inet_ntoa(f->u.addrs.mask));
    }

    return f;
}
