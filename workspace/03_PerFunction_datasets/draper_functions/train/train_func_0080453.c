evdns_base_nameserver_add(struct evdns_base *base, unsigned long int address)
{
	struct sockaddr_in sin;
	int res;
	sin.sin_addr.s_addr = address;
	sin.sin_port = htons(53);
	sin.sin_family = AF_INET;
	EVDNS_LOCK(base);
	res = _evdns_nameserver_add_impl(base, (struct sockaddr*)&sin, sizeof(sin));
	EVDNS_UNLOCK(base);
	return res;
}
