do_server(unsigned short port, int tcp, int ssl, int threads)
{
	handler *h = handler_create(threads);

	if (ssl)
		handler_set_tls(h, "server.pem");

	if (!handler_add_uncle(h, NULL, (short)g_uncle, SCOPE_DEFAULT))
	{
		printf("add uncle *failed\n");
		return;
	}

	if (!handler_add_server(h, &on_server_session, NULL, NULL, port, tcp, ssl, g_service))
	{
		printf("add server failed\n");
		return;
	}

	handler_wait(h);
	handler_destroy(h);
}
