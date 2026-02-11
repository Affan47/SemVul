_gethtbyaddr(addr, len, af)
	const char *addr;
	size_t len;
	int af;
{
	struct hostent *p;

	_sethtent(0);
	while ((p = _gethtent()))
		if (p->h_addrtype == af && !bcmp(p->h_addr, addr, len))
			break;
	_endhtent();
	return (p);
}
