jack_port_recalculate_latency (jack_port_t *port, jack_latency_callback_mode_t mode)
{
	jack_latency_range_t latency = { UINT32_MAX, 0 };
	JSList *node;

	pthread_mutex_lock (&port->connection_lock);
	for (node = port->connections; node; node = jack_slist_next (node)) {
		jack_port_t *other = node->data;
		jack_latency_range_t other_latency;

		jack_port_get_latency_range (other, mode, &other_latency);

		if (other_latency.max > latency.max)
			latency.max = other_latency.max;
		if (other_latency.min < latency.min)
			latency.min = other_latency.min;

	}
	pthread_mutex_unlock (&port->connection_lock);

	if (latency.min == UINT32_MAX)
		latency.min = 0;

	jack_port_set_latency_range (port, mode, &latency);
}
