client_free(RADCLIENT *client)
{
#ifdef WITH_DYNAMIC_CLIENTS
	if (client->dynamic == 2) {
		time_t now;

		if (!deleted_clients) {
			deleted_clients = fr_fifo_create(1024,
							 (void *) client_free);
			if (!deleted_clients) return;
		}


		client->dynamic = 3;
		client->created = now = time(NULL);
		fr_fifo_push(deleted_clients, client);


		client = fr_fifo_peek(deleted_clients);
		if ((client->created + 120) >= now) return;

		client = fr_fifo_pop(deleted_clients);
		rad_assert(client != NULL);
	}
#endif

	free(client->longname);
	free(client->secret);
	free(client->shortname);
	free(client->nastype);
	free(client->login);
	free(client->password);
	free(client->server);

#ifdef WITH_STATS
	free(client->auth);
#ifdef WITH_ACCOUNTING
	free(client->acct);
#endif
#endif

#ifdef WITH_DYNAMIC_CLIENTS
	free(client->client_server);
#endif

	free(client);
}
