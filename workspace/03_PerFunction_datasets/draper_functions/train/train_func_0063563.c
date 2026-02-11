oss_driver_write (oss_driver_t *driver, jack_nframes_t nframes)
{
	int channel;
	jack_sample_t *portbuf;
	JSList *node;
	jack_port_t *port;

	if (!driver->run) return 0;
	if (nframes != driver->period_size)
	{
		jack_error(
			"OSS: write failed nframes != period_size  (%u/%u): %s@%i",
			nframes, driver->period_size, __FILE__, __LINE__);
		return -1;
	}

	pthread_mutex_lock(&driver->mutex_out);

	node = driver->playback_ports;
	channel = 0;
	while (node != NULL)
	{
		port = (jack_port_t *) node->data;

		if (jack_port_connected(port))
		{
			portbuf = jack_port_get_buffer(port, nframes);
			copy_and_convert_out(driver->outdevbuf, portbuf,
				nframes, channel,
				driver->playback_channels,
				driver->bits);
		}

		node = jack_slist_next(node);
		channel++;
	}

	pthread_mutex_unlock(&driver->mutex_out);

	return 0;
}
