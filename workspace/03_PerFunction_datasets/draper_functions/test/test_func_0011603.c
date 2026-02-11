source_registry_server_maybe_start_auth_session (ESourceRegistryServer *server,
                                                 const gchar *uid)
{
	AuthRequest *request;


	request = source_registry_server_auth_request_next (server, uid);

	if (request != NULL) {
		GSource *idle_source;


		idle_source = g_idle_source_new ();
		g_source_set_callback (
			idle_source,
			source_registry_server_start_auth_session_idle_cb,
			auth_request_ref (request),
			(GDestroyNotify) auth_request_unref);
		g_source_attach (idle_source, server->priv->main_context);
		g_source_unref (idle_source);

		auth_request_unref (request);
	}
}
