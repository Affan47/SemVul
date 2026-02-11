pre_get_xml (GDataParsable *parsable, GString *xml_string)
{
	GDataGDOrganizationPrivate *priv = GDATA_GD_ORGANIZATION (parsable)->priv;

	if (priv->relation_type != NULL)
		gdata_parser_string_append_escaped (xml_string, " rel='", priv->relation_type, "'");
	if (priv->label != NULL)
		gdata_parser_string_append_escaped (xml_string, " label='", priv->label, "'");

	if (priv->is_primary == TRUE)
		g_string_append (xml_string, " primary='true'");
	else
		g_string_append (xml_string, " primary='false'");
}
