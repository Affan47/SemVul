client_validate(RADCLIENT_LIST *clients, RADCLIENT *master, RADCLIENT *c)
{
	char buffer[128];


	if (master->server && !c->server) {
		c->server = strdup(master->server);
	}


	if (master->server &&
	     (strcmp(master->server, c->server) != 0)) {
		DEBUG("- Cannot add client %s: Virtual server %s is not the same as the virtual server for the network.",
		      ip_ntoh(&c->ipaddr,
			      buffer, sizeof(buffer)),
		      c->server);

		goto error;
	}

	if (!client_add(clients, c)) {
		DEBUG("- Cannot add client %s: Internal error",
		      ip_ntoh(&c->ipaddr,
			      buffer, sizeof(buffer)));

		goto error;
	}


	c->dynamic = TRUE;
	c->lifetime = master->lifetime;
	c->created = time(NULL);
	c->longname = strdup(c->shortname);

	DEBUG("- Added client %s with shared secret %s",
	      ip_ntoh(&c->ipaddr, buffer, sizeof(buffer)),
	      c->secret);

	return 1;

 error:
	client_free(c);
	return 0;
}
