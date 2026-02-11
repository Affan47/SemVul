inet_proto_a2n(const char *buf)
{
	static char ncache[16];
	static int icache = -1;
	struct protoent *pe;

	if (icache>=0 && strcmp(ncache, buf) == 0)
		return icache;

	if (buf[0] >= '0' && buf[0] <= '9') {
		__u8 ret;
		if (get_u8(&ret, buf, 10))
			return -1;
		return ret;
	}

	pe = getprotobyname(buf);
	if (pe) {
		icache = pe->p_proto;
		strncpy(ncache, pe->p_name, 16);
		return pe->p_proto;
	}
	return -1;
}
