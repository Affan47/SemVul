post_parse_xml (GDataParsable *parsable, gpointer user_data, GError **error)
{
	GDataGContactEventPrivate *priv = GDATA_GCONTACT_EVENT (parsable)->priv;


	if (g_date_valid (&(priv->date)) == FALSE)
		return gdata_parser_error_required_element_missing ("gd:when", "gContact:event", error);

	return TRUE;
}
