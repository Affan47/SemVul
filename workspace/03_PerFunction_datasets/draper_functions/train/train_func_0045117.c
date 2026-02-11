delete_metadata_decomposed (TrackerProperty  *property,
                            const gchar      *value,
                            gint              value_id,
                            GError          **error)
{
	gboolean            multiple_values;
	const gchar        *table_name;
	const gchar        *field_name;
	TrackerProperty   **super_properties;
	GValue gvalue = { 0 };
	GValueArray        *old_values;
	GError             *new_error = NULL;
	gboolean            change = FALSE;

	multiple_values = tracker_property_get_multiple_values (property);
	table_name = tracker_property_get_table_name (property);
	field_name = tracker_property_get_name (property);


	old_values = get_old_property_values (property, &new_error);
	if (new_error) {

		g_clear_error (&new_error);
		return FALSE;
	}

	if (value) {
		string_to_gvalue (value, tracker_property_get_data_type (property), &gvalue, &new_error);
		if (new_error) {
			g_propagate_error (error, new_error);
			return FALSE;
		}
	} else {
		g_value_init (&gvalue, G_TYPE_INT64);
		g_value_set_int64 (&gvalue, value_id);
	}

	if (!value_set_remove_value (old_values, &gvalue)) {

		g_value_unset (&gvalue);
	} else {
		cache_delete_value (table_name, field_name,
		                    tracker_property_get_transient (property),
		                    &gvalue, multiple_values,
		                    tracker_property_get_fulltext_indexed (property),
		                    tracker_property_get_data_type (property) == TRACKER_PROPERTY_TYPE_DATETIME);

		if (!multiple_values) {
			TrackerClass **domain_index_classes;

			domain_index_classes = tracker_property_get_domain_indexes (property);

			while (*domain_index_classes) {
				if (resource_in_domain_index_class (*domain_index_classes)) {
					GValue gvalue_copy = { 0 };
					g_value_init (&gvalue_copy, G_VALUE_TYPE (&gvalue));
					g_value_copy (&gvalue, &gvalue_copy);
					cache_delete_value (tracker_class_get_name (*domain_index_classes),
					                    field_name,
					                    tracker_property_get_transient (property),
					                    &gvalue_copy, multiple_values,
					                    tracker_property_get_fulltext_indexed (property),
					                    tracker_property_get_data_type (property) == TRACKER_PROPERTY_TYPE_DATETIME);
				}
				domain_index_classes++;
			}
		}

		change = TRUE;
	}


	super_properties = tracker_property_get_super_properties (property);
	while (*super_properties) {
		change |= delete_metadata_decomposed (*super_properties, value, value_id, error);
		super_properties++;
	}

	return change;
}
