gigolo_bookmark_new_from_uri(const gchar *name, const gchar *uri)
{
	GigoloBookmark *bm = g_object_new(GIGOLO_BOOKMARK_TYPE, NULL);
	GigoloBookmarkPrivate *priv = GIGOLO_BOOKMARK_GET_PRIVATE(bm);

	gigolo_bookmark_set_name(bm, name);
	if (! gigolo_bookmark_parse_uri(bm, uri))
		priv->is_valid = FALSE;

	return bm;
}
