gm_world_reconnect(GmWorld *world) {
	world->priv->reconnect_id = 0;
	const gchar *host, *port;

	host = gm_net_current_host(world->priv->net);
	port = gm_net_current_port(world->priv->net);

	if (!host) {
		host = gm_options_get(world->priv->options, "host");
	}
	if (!port) {
		port = gm_options_get(world->priv->options, "port");
	}

	gm_world_connect_to(world, host, port);
	return FALSE;
}
