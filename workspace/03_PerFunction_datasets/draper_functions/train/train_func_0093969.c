transport_new(rdpSettings* settings)
{
	rdpTransport* transport;

	transport = (rdpTransport*) xzalloc(sizeof(rdpTransport));

	if (transport != NULL)
	{
		transport->tcp = tcp_new(settings);
		transport->settings = settings;


		transport->ts.tv_sec = 0;
		transport->ts.tv_nsec = 100000;


		transport->recv_buffer = stream_new(BUFFER_SIZE);


		transport->recv_stream = stream_new(BUFFER_SIZE);
		transport->send_stream = stream_new(BUFFER_SIZE);

		transport->blocking = True;
	}

	return transport;
}
