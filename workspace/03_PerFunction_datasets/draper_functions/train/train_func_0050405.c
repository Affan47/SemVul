piaddrcidr(const struct iaddr *addr, unsigned int bits) {
	static char
	    ret[sizeof("ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255/128")];


	if (bits > (addr->len * 8))
		return NULL;

	sprintf(ret, "%s/%d", piaddr(*addr), bits);

	return ret;
}
