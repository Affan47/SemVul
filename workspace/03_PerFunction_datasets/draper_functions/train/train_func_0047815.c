post_parse_xml (GDataParsable *parsable, gpointer user_data, GError **error)
{
	GDataFeedPrivate *priv = GDATA_FEED (parsable)->priv;


	if (priv->id == NULL)
		return gdata_parser_error_required_element_missing ("id", "feed", error);
	if (priv->updated == -1)
		return gdata_parser_error_required_element_missing ("updated", "feed", error);


	priv->entries = g_list_reverse (priv->entries);
	priv->categories = g_list_reverse (priv->categories);
	priv->links = g_list_reverse (priv->links);
	priv->authors = g_list_reverse (priv->authors);

	return TRUE;
}
