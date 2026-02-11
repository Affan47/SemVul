jack_client_unload (jack_client_internal_t *client)
{
	if (client->handle) {
		if (client->finish) {
			client->finish (client->private_client->process_arg);
		}
		dlclose (client->handle);
	}
}
