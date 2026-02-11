jack_port_new (const jack_client_t *client, jack_port_id_t port_id,
	       jack_control_t *control)
{
	jack_port_shared_t *shared = &control->ports[port_id];
	jack_port_type_id_t ptid = shared->ptype_id;
	jack_port_t *port;

	if ((port = (jack_port_t *) malloc (sizeof (jack_port_t))) == NULL) {
		return NULL;
	}

	port->mix_buffer = NULL;
	port->client_segment_base = NULL;
	port->shared = shared;
	port->type_info = &client->engine->port_types[ptid];
	pthread_mutex_init (&port->connection_lock, NULL);
	port->connections = 0;
	port->tied = NULL;

	if (client->control->id == port->shared->client_id) {


		jack_port_functions_t *port_functions = jack_get_port_functions(ptid);
		if (port_functions == NULL)
			port_functions = &jack_builtin_NULL_functions;
		port->fptr = *port_functions;
		port->shared->has_mixdown = (port->fptr.mixdown ? TRUE : FALSE);
	}


	port->client_segment_base =
		(void **) &client->port_segment[ptid].attached_at;

	return port;
}
