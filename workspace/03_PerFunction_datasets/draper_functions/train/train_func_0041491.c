jack_port_get_latency_range (jack_port_t *port, jack_latency_callback_mode_t mode, jack_latency_range_t *range)
{
	if (mode == JackCaptureLatency)
		*range = port->shared->capture_latency;
	else
		*range = port->shared->playback_latency;
}
