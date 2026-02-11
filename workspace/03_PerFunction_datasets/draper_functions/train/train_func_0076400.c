invoke_link_if_present (GtkTextBuffer *buffer,
                        GtkTextIter *iter)
{
	gboolean res;
	gchar *url;

	g_return_val_if_fail (buffer != NULL, FALSE);

	url = get_url_at_iter (buffer, iter);

	res = url && *url;
	if (res)
		e_show_uri (NULL, url);

	g_free (url);

	return res;
}
