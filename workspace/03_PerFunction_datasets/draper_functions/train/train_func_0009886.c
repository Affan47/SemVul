pre_get_xml (GDataParsable *parsable, GString *xml_string)
{
	GDataGDWhenPrivate *priv = GDATA_GD_WHEN (parsable)->priv;
	gchar *start_time;

	if (priv->is_date == TRUE)
		start_time = gdata_parser_date_from_int64 (priv->start_time);
	else
		start_time = gdata_parser_int64_to_iso8601 (priv->start_time);

	g_string_append_printf (xml_string, " startTime='%s'", start_time);
	g_free (start_time);

	if (priv->end_time != -1) {
		gchar *end_time;

		if (priv->is_date == TRUE)
			end_time = gdata_parser_date_from_int64 (priv->end_time);
		else
			end_time = gdata_parser_int64_to_iso8601 (priv->end_time);

		g_string_append_printf (xml_string, " endTime='%s'", end_time);
		g_free (end_time);
	}

	if (priv->value_string != NULL)
		gdata_parser_string_append_escaped (xml_string, " valueString='", priv->value_string, "'");
}
