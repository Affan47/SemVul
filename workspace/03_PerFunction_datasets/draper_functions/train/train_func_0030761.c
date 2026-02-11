authenticate_cb (SoupSession *session,
                 SoupMessage *msg,
                 SoupAuth *auth,
                 gboolean retrying,
                 gpointer user_data)
{
	EOwncloudAuthenticator *authenticator = user_data;

	g_return_if_fail (authenticator != NULL);

	if (retrying || !authenticator->password) {
		ESourceRegistryServer *server;
		EAuthenticationSession *auth_session;
		ESource *source;

		source = e_backend_get_source (
			E_BACKEND (authenticator->collection));
		server = e_collection_backend_ref_server (
			authenticator->collection);

		auth_session = e_source_registry_server_new_auth_session (
			server,
			E_SOURCE_AUTHENTICATOR (authenticator),
			e_source_get_uid (source));
		if (!e_source_registry_server_authenticate_sync (server, auth_session, NULL, NULL)) {
			if (authenticator->password)
				g_string_free (authenticator->password, TRUE);
			authenticator->password = NULL;
		}

		g_object_unref (auth_session);
		g_object_unref (server);
	}

	if (authenticator->username && authenticator->password)
		soup_auth_authenticate (
			auth, authenticator->username,
			authenticator->password->str);
}
