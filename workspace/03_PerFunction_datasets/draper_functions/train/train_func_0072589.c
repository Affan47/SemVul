jdns_nameserver_copy(const jdns_nameserver_t *a)
{
	jdns_nameserver_t *c = jdns_nameserver_new();
	if(a->address)
		c->address = jdns_address_copy(a->address);
	c->port = a->port;
	return c;
}
