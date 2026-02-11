jack_port_get_connections (const jack_port_t *port)
{
	const char **ret = NULL;
	JSList *node;
	unsigned int n;


	pthread_mutex_lock (&((jack_port_t *) port)->connection_lock);

	if (port->connections != NULL) {

		ret = (const char **)
			malloc (sizeof (char *)
				* (jack_slist_length (port->connections) + 1));
		if (ret == NULL) {
			pthread_mutex_unlock (&((jack_port_t *)port)->connection_lock);
			return NULL;
		}

		for (n = 0, node = port->connections; node;
		     node = jack_slist_next (node), ++n) {
			jack_port_t* other =(jack_port_t *) node->data;
			ret[n] = other->shared->name;
		}
		ret[n] = NULL;
	}

	pthread_mutex_unlock (&((jack_port_t *) port)->connection_lock);
	return ret;
}
