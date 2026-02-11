get_xml (GDataParsable *parsable, GString *xml_string)
{
	GDataGeoRSSWherePrivate *priv = GDATA_GEORSS_WHERE (parsable)->priv;
	gchar latitude_str[G_ASCII_DTOSTR_BUF_SIZE];
	gchar longitude_str[G_ASCII_DTOSTR_BUF_SIZE];

	if (priv->latitude != G_MAXDOUBLE && priv->longitude != G_MAXDOUBLE) {
		g_string_append_printf (xml_string, "<gml:Point><gml:pos>%s %s</gml:pos></gml:Point>",
		                        g_ascii_dtostr (latitude_str, sizeof (latitude_str), priv->latitude),
		                        g_ascii_dtostr (longitude_str, sizeof (longitude_str), priv->longitude));
	}
}
