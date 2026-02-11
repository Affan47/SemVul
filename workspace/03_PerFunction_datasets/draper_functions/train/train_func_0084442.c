source_backend_summary_setup_set_property (GObject *object,
                                         guint property_id,
                                         const GValue *value,
                                         GParamSpec *pspec)
{
	switch (property_id) {
		case PROP_SUMMARY_FIELDS:
		case PROP_INDEXED_FIELDS:
			source_backend_summary_setup_set_literal_fields (
				E_SOURCE_BACKEND_SUMMARY_SETUP (object),
				g_value_get_string (value), property_id);
			return;
	}

	G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
}
