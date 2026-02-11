tracker_ontologies_get_class_string_gvdb (const gchar *uri,
                                          const gchar *predicate)
{
	GVariant *value;
	const gchar *result;

	value = tracker_ontologies_get_class_value_gvdb (uri, predicate);

	if (value == NULL) {
		return NULL;
	}

	result = g_variant_get_string (value, NULL);
	g_variant_unref (value);

	return result;
}
