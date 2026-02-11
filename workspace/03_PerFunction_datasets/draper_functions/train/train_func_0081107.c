ipvs_cmp_services(ipvs_service_entry_t *s1, ipvs_service_entry_t *s2)
{
	int r, i;

	r = s1->fwmark - s2->fwmark;
	if (r != 0)
		return r;

	r = s1->af - s2->af;
	if (r != 0)
		return r;

	r = s1->protocol - s2->protocol;
	if (r != 0)
		return r;

	if (s1->af == AF_INET6)
		for (i = 0; !r && (i < 4); i++)
			r = ntohl(s1->addr.in6.s6_addr32[i]) - ntohl(s2->addr.in6.s6_addr32[i]);
	else
		r = ntohl(s1->addr.ip) - ntohl(s2->addr.ip);
	if (r != 0)
		return r;

	return ntohs(s1->port) - ntohs(s2->port);
}
