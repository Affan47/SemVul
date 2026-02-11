go_doc_set_uri (GODoc *doc, char const *uri)
{
	char *new_uri;

	g_return_val_if_fail (doc != NULL, FALSE);

	if (go_str_compare (uri, doc->uri) == 0)
		return TRUE;

	new_uri = g_strdup (uri);
	g_free (doc->uri);
	doc->uri = new_uri;


	g_object_notify (G_OBJECT (doc), "uri");

	return TRUE;
}
