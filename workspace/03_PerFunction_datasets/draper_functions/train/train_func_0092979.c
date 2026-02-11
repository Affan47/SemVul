process_domain_indexes (TrackerProperty *property,
                        GValue          *gvalue,
                        const gchar     *field_name,
                        const gchar     *graph,
                        gint             graph_id)
{
	TrackerClass **domain_index_classes;

	domain_index_classes = tracker_property_get_domain_indexes (property);
	while (*domain_index_classes) {
		if (resource_in_domain_index_class (*domain_index_classes)) {
			GValue gvalue_copy = { 0 };

			g_value_init (&gvalue_copy, G_VALUE_TYPE (gvalue));
			g_value_copy (gvalue, &gvalue_copy);

			cache_insert_value (tracker_class_get_name (*domain_index_classes),
			                    field_name,
			                    tracker_property_get_transient (property),
			                    &gvalue_copy,
			                    graph != NULL ? ensure_resource_id (graph, NULL) : graph_id,
			                    FALSE,
			                    tracker_property_get_fulltext_indexed (property),
			                    tracker_property_get_data_type (property) == TRACKER_PROPERTY_TYPE_DATETIME);
		}
		domain_index_classes++;
	}
}
