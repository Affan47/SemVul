gigolo_bookmark_set_uri(GigoloBookmark *bookmark, const gchar *uri)
{
	GigoloBookmarkPrivate *priv;
	GigoloBookmark *tmp;

	g_return_if_fail(bookmark != NULL);
	g_return_if_fail(NZV(uri));

	priv = GIGOLO_BOOKMARK_GET_PRIVATE(bookmark);

	tmp = gigolo_bookmark_new_from_uri(priv->name, uri);
	if (gigolo_bookmark_is_valid(tmp))
		gigolo_bookmark_clone(bookmark, tmp);

	g_object_unref(tmp);
}
