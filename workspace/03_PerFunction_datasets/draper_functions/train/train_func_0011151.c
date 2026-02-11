gigolo_bookmark_get_uri_real(GigoloBookmark *bookmark, gboolean escaped)
{
	GigoloBookmarkPrivate *priv = GIGOLO_BOOKMARK_GET_PRIVATE(bookmark);
	gchar *result;
	const gchar *domain = NULL;
	gchar *user = NULL;
	gchar *port = NULL;

	g_return_val_if_fail(bookmark != NULL, NULL);

	if (priv->port > 0 && priv->port != gigolo_get_default_port(priv->scheme))
	{
		port = g_strdup_printf(":%d", priv->port);
	}


	if (escaped && NZV(priv->user))
		user = g_uri_escape_string(priv->user, G_URI_RESERVED_CHARS_ALLOWED_IN_USERINFO, FALSE);
	else
		user = g_strdup(priv->user);

	domain = gigolo_bookmark_get_domain(bookmark);

	result = g_strdup_printf("%s://%s%s%s%s%s%s/%s%s%s",
		priv->scheme,
		(NZV(domain)) ? domain : "",
		(NZV(domain)) ? ";" : "",
		(NZV(user)) ? user : "",
		(NZV(user) || NZV(domain)) ? "@" : "",
		priv->host,
		(port) ? port : "",
		(NZV(priv->path)) ? priv->path : "",
		(NZV(priv->share)) ? priv->share : "",
		(NZV(priv->share)) ? "/" : "");

	g_free(port);
	g_free(user);
	return result;
}
