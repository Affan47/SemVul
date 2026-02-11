transport_read(rdpTransport* transport, STREAM* s)
{
	int status = -1;

	if (transport->layer == TRANSPORT_LAYER_TLS)
		status = tls_read(transport->tls, s->data, s->size);
	else if (transport->layer == TRANSPORT_LAYER_TCP)
		status = tcp_read(transport->tcp, s->data, s->size);

	return status;
}
