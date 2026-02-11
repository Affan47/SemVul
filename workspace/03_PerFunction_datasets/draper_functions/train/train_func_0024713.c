turtle_load_ontology (const gchar *turtle_subject,
                      const gchar *turtle_predicate,
                      const gchar *turtle_object)
{

	if (!g_strcmp0 (turtle_predicate, IS)) {
		known_items = g_list_prepend (known_items, g_strdup (turtle_subject));
	}
}
