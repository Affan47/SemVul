jdns_server_copy(const jdns_server_t *s)
{
	jdns_server_t *c = jdns_server_new();
	if(s->name)
		c->name = _ustrdup(s->name);
	c->port = s->port;
	c->priority = s->priority;
	c->weight = s->weight;
	return c;
}
