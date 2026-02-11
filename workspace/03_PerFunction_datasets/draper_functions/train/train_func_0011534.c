pre_parse_xml (GDataParsable *parsable, xmlDoc *doc, xmlNode *root_node, gpointer user_data, GError **error)
{
	GDataMediaCategoryPrivate *priv = GDATA_MEDIA_CATEGORY (parsable)->priv;
	xmlChar *category, *scheme;

	category = xmlNodeListGetString (doc, root_node->children, TRUE);
	if (category == NULL || *category == '\0') {
		xmlFree (category);
		return gdata_parser_error_required_content_missing (root_node, error);
	}

	scheme = xmlGetProp (root_node, (xmlChar*) "scheme");
	if (scheme != NULL && *scheme == '\0') {
		xmlFree (scheme);
		xmlFree (category);
		return gdata_parser_error_required_property_missing (root_node, "scheme", error);
	} else if (scheme == NULL) {

		scheme = xmlStrdup ((xmlChar*) "http://video.search.yahoo.com/mrss/category_schema");
	}

	priv->category = (gchar*) category;
	priv->scheme = (gchar*) scheme;
	priv->label = (gchar*) xmlGetProp (root_node, (xmlChar*) "label");

	return TRUE;
}
