content_xml_text_handler (GMarkupParseContext   *context,
                          const gchar           *text,
                          gsize                  text_len,
                          gpointer               user_data,
                          GError               **error)
{
	OPFContentData *content_data = user_data;
	gsize written_bytes = 0;

	if (text_len <= 0) {
		return;
	}

	if (tracker_text_validate_utf8 (text,
	                                MIN (text_len, content_data->limit),
	                                &content_data->contents,
	                                &written_bytes)) {
		if (content_data->contents->str[content_data->contents->len - 1] != ' ') {
			g_string_append_c (content_data->contents, ' ');
		}
	}

	content_data->limit -= written_bytes;
}
