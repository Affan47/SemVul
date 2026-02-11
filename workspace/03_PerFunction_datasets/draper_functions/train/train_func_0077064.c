gigolo_bookmark_set_domain(GigoloBookmark *bookmark, const gchar *domain)
{
	GigoloBookmarkPrivate *priv;

	g_return_if_fail(bookmark != NULL);
	g_return_if_fail(domain != NULL);

	priv = GIGOLO_BOOKMARK_GET_PRIVATE(bookmark);

	g_free(priv->domain);
	priv->domain = g_strdup(domain);
}
