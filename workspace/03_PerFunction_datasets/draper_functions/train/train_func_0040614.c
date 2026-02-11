jack_client_disconnect_ports (jack_engine_t *engine,
			      jack_client_internal_t *client)
{
	JSList *node;
	jack_port_internal_t *port;


	for (node = client->ports; node; node = jack_slist_next (node)) {
		port = (jack_port_internal_t *) node->data;
		jack_port_clear_connections (engine, port);
		jack_port_registration_notify (engine, port->shared->id, FALSE);
		jack_port_release (engine, port);
	}

	jack_slist_free (client->ports);
	jack_slist_free (client->truefeeds);
	jack_slist_free (client->sortfeeds);
	client->truefeeds = 0;
	client->sortfeeds = 0;
	client->ports = 0;
}
