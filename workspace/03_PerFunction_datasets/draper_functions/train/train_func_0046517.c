host_name_to_addr4(const char *name, struct in_addr *addr)
{
	struct hostent *hptr;
	unsigned char buf[HOSTENT_SIZE];

	assert(name != NULL);
	assert(addr != NULL);

	if (!(hptr = get_host_by_name(name, buf, sizeof(buf), NULL)))
		return(-1);
	if (hptr->h_length > 4) {
		errno = ERANGE;
		return(-1);
	}
	memcpy(addr, hptr->h_addr_list[0], hptr->h_length);
	return(0);
}
