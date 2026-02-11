parse_xml (GDataParsable *parsable, xmlDoc *doc, xmlNode *node, gpointer user_data, GError **error)
{
	GDataYouTubeCategory *self = GDATA_YOUTUBE_CATEGORY (parsable);

	if (gdata_parser_is_namespace (node, "http://gdata.youtube.com/schemas/2007") == TRUE) {
		if (xmlStrcmp (node->name, (xmlChar*) "assignable") == 0) {

			self->priv->assignable = TRUE;
		} else if (xmlStrcmp (node->name, (xmlChar*) "deprecated") == 0) {

			self->priv->assignable = FALSE;
			g_strfreev (self->priv->browsable_regions);
			self->priv->browsable_regions = NULL;
		} else if (xmlStrcmp (node->name, (xmlChar*) "browsable") == 0) {

			xmlChar *regions;

			regions = xmlGetProp (node, (xmlChar*) "regions");
			if (regions == NULL)
				return gdata_parser_error_required_property_missing (node, "regions", error);

			self->priv->browsable_regions = g_strsplit ((gchar*) regions, " ", -1);
		} else {
			return GDATA_PARSABLE_CLASS (gdata_youtube_category_parent_class)->parse_xml (parsable, doc, node, user_data, error);
		}
	} else {
		return GDATA_PARSABLE_CLASS (gdata_youtube_category_parent_class)->parse_xml (parsable, doc, node, user_data, error);
	}

	return TRUE;
}
