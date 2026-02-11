csv_parser_field_read_cb (char *s, size_t len, void *data)
{
	CsvParserData *pdata = (CsvParserData* ) data;
	GdaDataModelImport *model = pdata->model;
	GValue *value = NULL;
	GdaColumn *column;
	GType type = GDA_TYPE_NULL;
	gchar *copy;

	if (pdata->model->priv->extract.csv.ignore_first_line)
		return;


	if (model->priv->extract.csv.encoding) {
		GError *error = NULL;
		copy = g_convert (s, len, "UTF-8", model->priv->extract.csv.encoding,
				  NULL, NULL, &error);
		if (!copy) {
			gchar *str;
			str = g_strdup_printf (_("Character conversion at line %d, error: %s"),
					       model->priv->extract.csv.text_line,
					       error && error->message ? error->message:
					       _("no detail"));
			add_error (model, str);
			g_free (str);
			g_error_free (error);
		}
	}
	else
		copy = g_locale_to_utf8 (s, len, NULL, NULL, NULL);
	if (!copy)
		copy = g_strndup (s, len);


	if (! model->priv->extract.csv.initializing) {
		if (pdata->field_next_col >= pdata->nb_cols) {

			g_free (copy);
			return;
		}
		column = gda_data_model_describe_column ((GdaDataModel *) model,
							 pdata->field_next_col);
		pdata->field_next_col++;

		if (!column) {
			g_free (copy);
			return;
		}
		type = gda_column_get_g_type (column);
	}
	else
		type = G_TYPE_STRING;


	if (type != GDA_TYPE_BINARY) {
		if (! g_ascii_strcasecmp (copy, "NULL"))
			value = gda_value_new_null ();
		else {
			value = gda_value_new_from_string (copy, type);
			if (!value) {
				gchar *str;
				str = g_strdup_printf (_("Could not convert string '%s' to a '%s' value"), copy,
						       g_type_name (type));
				add_error (model, str);
				g_free (str);
			}
		}
	}
	else
		value = gda_value_new_binary ((guchar*) s, len);
	g_free (copy);
	pdata->fields = g_slist_prepend (pdata->fields, value);
	pdata->nb_cols ++;

}
