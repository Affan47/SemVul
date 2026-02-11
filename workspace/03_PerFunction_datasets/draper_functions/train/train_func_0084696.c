host_lookup(unsigned int in, int use_mode)
{
 	static char hostname_buf[BUFSIZE] = {0};
	static int hostname_idx = 0;
	struct in_addr addr;
	char *name, *retval;
	int len;
	struct hostent *host_ent;
	struct resolv_item *r;

	addr.s_addr = in;
	host_ent = NULL;

	if (in == 0)
		return inet_ntoa(addr);
	r = NULL;
	switch (use_mode) {
	    case HL_MODE_NAME:
		if (!(r = resolv_get(in))) {
			host_ent = gethostbyaddr((char *)&addr, sizeof(struct in_addr),
						AF_INET);
			if(!host_ent)
		        	name = inet_ntoa(addr);
			else
				name = host_ent->h_name;
		} else
			name = r->name;
		break;
	    case HL_MODE_DEFERRED:
		if (!(r = resolv_get(in))) {
			resolv_request(in);
			name = inet_ntoa(addr);
		} else
			name = r->name;
		break;
	    case HL_MODE_NR:
	    default:
		name = inet_ntoa(addr);
		break;
	}

	len = strlen(name);
	if (len + hostname_idx + 1 > sizeof(hostname_buf))
		hostname_idx = 0;
	strcpy((retval = hostname_buf + hostname_idx), name);
	hostname_idx += len + 1;
	if (r)
		resolv_release(r);
	return retval;
}
