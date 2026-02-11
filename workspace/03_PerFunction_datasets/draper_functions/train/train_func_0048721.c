jack_port_by_name (jack_client_t *client,  const char *port_name)
{
	JSList *node;
	jack_port_t* port;
	for (node = client->ports_ext; node; node = jack_slist_next (node)) {
		port = node->data;
		if (jack_port_name_equals (port->shared, port_name)) {

			return port;
		}
	}


	port = jack_port_by_name_int (client, port_name);
	if (port != NULL)
		client->ports_ext =
			jack_slist_prepend (client->ports_ext, port);
	return port;
}
