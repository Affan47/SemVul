gethname(u_int32_t a)
{
	register int32_t options;
	register struct hostent *hp;

	options = _res.options;
	_res.options |= RES_AAONLY;
	_res.options &= ~(RES_DEFNAMES | RES_DNSRCH);
	hp = gethostbyaddr((char *)&a, sizeof(a), AF_INET);
	_res.options = options;
	if (hp == NULL)
		return (intoa(a));
	return (hp->h_name);
}
