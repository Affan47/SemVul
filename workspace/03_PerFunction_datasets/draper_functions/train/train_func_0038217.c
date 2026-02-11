tracker_ontologies_get_property_by_uri (const gchar *uri)
{
	TrackerProperty *property;

	g_return_val_if_fail (uri != NULL, NULL);

	property = g_hash_table_lookup (property_uris, uri);

	if (!property && gvdb_table) {
		if (tracker_ontologies_get_property_string_gvdb (uri, "name") != NULL) {
			property = tracker_property_new (TRUE);
			tracker_property_set_uri (property, uri);

			g_hash_table_insert (property_uris,
				             g_strdup (uri),
				             property);
		}
	}

	return property;
}
