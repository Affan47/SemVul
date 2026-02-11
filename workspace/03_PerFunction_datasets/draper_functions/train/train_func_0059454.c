oss_driver_read (oss_driver_t *driver, jack_nframes_t nframes)
{
	int channel;
	jack_sample_t *portbuf;
	JSList *node;
	jack_port_t *port;

	if (!driver->run) return 0;
	if (nframes != driver->period_size)
	{
		jack_error(
			"OSS: read failed nframes != period_size  (%u/%u): %s@%i",
			nframes, driver->period_size, __FILE__, __LINE__);
		return -1;
	}

	pthread_mutex_lock(&driver->mutex_in);

	node = driver->capture_ports;
	channel = 0;
	while (node != NULL)
	{
		port = (jack_port_t *) node->data;

		if (jack_port_connected(port))
		{
			portbuf = jack_port_get_buffer(port, nframes);
			copy_and_convert_in(portbuf, driver->indevbuf,
				nframes, channel,
				driver->capture_channels,
				driver->bits);
		}

		node = jack_slist_next(node);
		channel++;
	}

	pthread_mutex_unlock(&driver->mutex_in);

	return 0;
}
