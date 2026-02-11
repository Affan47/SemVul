bind_builder_uint_enum (GtkBuilder *builder,
			GSettings *settings,
			const char *widget_name,
			const char *prefs,
			const guint64 *values,
			int n_values)
{
	UIntEnumBinding *binding;

	binding = g_new (UIntEnumBinding, 1);
	binding->values = values;
	binding->n_values = n_values;

	g_settings_bind_with_mapping (settings, prefs,
				      gtk_builder_get_object (builder, widget_name),
				      "active", G_SETTINGS_BIND_DEFAULT,
				      uint_enum_get_mapping,
				      uint_enum_set_mapping,
				      binding, g_free);
}
