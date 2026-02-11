force_styles (GtkSourceLanguage *language)
{


	if (!language->priv->styles_loaded && language->priv->ctx_data == NULL)
	{
		GtkSourceContextData *ctx_data;

		ctx_data = gtk_source_language_parse_file (language);
		if (ctx_data == NULL)
			return FALSE;

		language->priv->styles_loaded = TRUE;
		_gtk_source_context_data_unref (ctx_data);
	}

	return TRUE;
}
