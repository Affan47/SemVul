load_customization (GdaDDLCreator *ddlc, const gchar *xml_spec_file, GError **error)
{
	xmlNodePtr node;
	xmlDocPtr doc;


	doc = xmlParseFile (xml_spec_file);
	if (!doc) {
		g_set_error (error, GDA_DDL_CREATOR_ERROR, GDA_DDL_CREATOR_SPECFILE_NOT_FOUND_ERROR,
			     _("Could not load file '%s'"), xml_spec_file);
		return FALSE;
	}

	node = xmlDocGetRootElement (doc);
	if (!node || strcmp ((gchar *) node->name, "schema")) {
		g_set_error (error, GDA_DDL_CREATOR_ERROR, GDA_DDL_CREATOR_INCORRECT_SCHEMA_ERROR,
			     _("Root node of file '%s' should be <schema>."), xml_spec_file);
		xmlFreeDoc (doc);
		return FALSE;
	}


	for (node = node->children; node; node = node->next) {

		if (!strcmp ((gchar *) node->name, "specifics")) {
			xmlNodePtr snode;
			for (snode = node->children; snode; snode = snode->next) {
				if (strcmp ((gchar *) snode->name, "provider"))
					continue;
				xmlChar *pname;
				pname = xmlGetProp (snode, BAD_CAST "name");
				if (!pname) {
					g_warning ("<provider> section ignored because no provider name specified");
					continue;
				}

				xmlNodePtr rnode;
				for (rnode = snode->children; rnode; rnode = rnode->next) {
					if (!strcmp ((gchar *) rnode->name, "replace") ||
					    !strcmp ((gchar *) rnode->name, "ignore")) {
						xmlChar *context, *tmp;
						context = xmlGetProp (rnode, BAD_CAST "context");
						if (!context) {
							g_warning ("<%s> section ignored because no context specified",
								   snode->name);
							continue;
						}
						ProviderSpecificKey *key = g_new0 (ProviderSpecificKey, 1);
						ProviderSpecificValue *val = g_new0 (ProviderSpecificValue, 1);
						key->prov = g_strdup ((gchar *) pname);
						key->path = g_strdup ((gchar *) context);
						xmlFree (context);
						tmp = xmlGetProp (rnode, BAD_CAST "expr");
						if (tmp) {
							key->expr = g_strdup ((gchar *) tmp);
							xmlFree (tmp);
						}
						tmp = xmlGetProp (rnode, BAD_CAST "replace_with");
						if (tmp) {
							val->repl = g_strdup ((gchar *) tmp);
							xmlFree (tmp);
						}
						g_hash_table_insert (ddlc->priv->provider_specifics, key, val);


					}
				}
				xmlFree (pname);
			}
		}
	}
	xmlFreeDoc (doc);

	return TRUE;
}
