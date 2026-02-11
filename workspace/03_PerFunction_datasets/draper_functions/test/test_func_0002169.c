soup_authenticate (SoupSession *session,
                   SoupMessage *msg,
                   SoupAuth *auth,
                   gboolean retrying,
                   gpointer data)
{
	ECalBackendHttp *cbhttp;
	ESourceAuthentication *auth_extension;
	ESource *source;
	const gchar *extension_name;

	cbhttp = E_CAL_BACKEND_HTTP (data);

	source = e_backend_get_source (E_BACKEND (data));
	extension_name = E_SOURCE_EXTENSION_AUTHENTICATION;
	auth_extension = e_source_get_extension (source, extension_name);

	if (!retrying && cbhttp->priv->password != NULL) {
		gchar *user;

		user = e_source_authentication_dup_user (auth_extension);
		soup_auth_authenticate (auth, user, cbhttp->priv->password);
		g_free (user);
	}
}
