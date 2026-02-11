make_address(const char *address, struct in_addr *ip)
{
    if(inet_aton(address, ip) == 0){


	struct hostent *he = gethostbyname(address);
	if(he) {
	    unsigned char *p = (unsigned char*)he->h_addr;
	    ip->s_addr = (p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3];
	} else {
	    return -1;
	}
    }
    return 0;
}
