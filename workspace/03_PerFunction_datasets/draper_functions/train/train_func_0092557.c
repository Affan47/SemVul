match_cidr(const char *s1, const char *s2)
{
	unsigned char ipaddr[IN6ADDRSZ], maskaddr[IN6ADDRSZ];
	char mask[BUFSIZE];
	char address[NICKLEN + USERLEN + HOSTLEN + 6];
	char *ipmask;
	char *ip;
	char *len;
	int cidrlen;

	strlcpy(mask, s1, sizeof mask);
	strlcpy(address, s2, sizeof address);

	ipmask = strrchr(mask, '@');
	if (ipmask == NULL)
		return 1;

	*ipmask++ = '\0';

	ip = strrchr(address, '@');
	if (ip == NULL)
		return 1;
	*ip++ = '\0';

	len = strrchr(ipmask, '/');
	if (len == NULL)
		return 1;

	*len++ = '\0';

	cidrlen = atoi(len);
	if (cidrlen == 0)
		return 1;

	if (strchr(ip, ':') && strchr(ipmask, ':'))
	{
		if (cidrlen > 128)
			return 1;
		if (!inet_pton6(ip, ipaddr))
			return 1;
		if (!inet_pton6(ipmask, maskaddr))
			return 1;
		return !comp_with_mask(ipaddr, maskaddr, cidrlen) ||
			match(mask, address);
	}
	else if (!strchr(ip, ':') && !strchr(ipmask, ':'))
	{
		if (cidrlen > 32)
			return 1;
		if (!inet_pton4(ip, ipaddr))
			return 1;
		if (!inet_pton4(ipmask, maskaddr))
			return 1;
		return !comp_with_mask(ipaddr, maskaddr, cidrlen) ||
			match(mask, address);
	}
	else
		return 1;
}
