soup_request_data_send (SoupRequest   *request,
			GCancellable  *cancellable,
			GError       **error)
{
	SoupRequestData *data = SOUP_REQUEST_DATA (request);
	SoupURI *uri = soup_request_get_uri (request);
	GInputStream *memstream;
	const char *comma, *start, *end;
	gboolean base64 = FALSE;
	char *uristr;

	uristr = soup_uri_to_string (uri, FALSE);
	start = uristr + 5;
	comma = strchr (start, ',');
	if (comma && comma != start) {

		if (comma > start + BASE64_INDICATOR_LEN && !g_ascii_strncasecmp (comma - BASE64_INDICATOR_LEN, BASE64_INDICATOR, BASE64_INDICATOR_LEN)) {
			end = comma - BASE64_INDICATOR_LEN;
			base64 = TRUE;
		} else
			end = comma;

		if (end != start)
			data->priv->content_type = soup_uri_decoded_copy (start, end - start, NULL);
	}

	memstream = g_memory_input_stream_new ();

	if (comma)
		start = comma + 1;

	if (*start) {
		int decoded_length = 0;
		guchar *buf = (guchar *) soup_uri_decoded_copy (start, strlen (start),
								&decoded_length);

		if (base64)
			buf = g_base64_decode_inplace ((gchar*) buf, &data->priv->content_length);
		else
			data->priv->content_length = decoded_length;

		g_memory_input_stream_add_data (G_MEMORY_INPUT_STREAM (memstream),
						buf, data->priv->content_length,
						g_free);
	}
	g_free (uristr);

	return memstream;
}
