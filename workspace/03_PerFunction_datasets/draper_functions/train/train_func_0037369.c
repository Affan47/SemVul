cd_dom_text_cb (GMarkupParseContext *context,
		const gchar         *text,
		gsize                text_len,
		gpointer             user_data,
		GError             **error)
{
	CdDom *dom = (CdDom *) user_data;
	CdDomNodeData *data;
	guint i;


	if (text_len == 0)
		return;


	for (i = 0; i < text_len; i++) {
		if (text[i] != ' ' &&
		    text[i] != '\n' &&
		    text[i] != '\t')
			break;
	}
	if (i >= text_len)
		return;


	data = dom->priv->current->data;
	g_string_append (data->cdata, text);
}
