soup_auth_authenticate (SoupAuth *auth, const char *username, const char *password)
{
	gboolean was_authenticated;

	g_return_if_fail (SOUP_IS_AUTH (auth));
	g_return_if_fail (username != NULL);
	g_return_if_fail (password != NULL);

	was_authenticated = soup_auth_is_authenticated (auth);
	SOUP_AUTH_GET_CLASS (auth)->authenticate (auth, username, password);
	if (was_authenticated != soup_auth_is_authenticated (auth))
		g_object_notify (G_OBJECT (auth), SOUP_AUTH_IS_AUTHENTICATED);
}
