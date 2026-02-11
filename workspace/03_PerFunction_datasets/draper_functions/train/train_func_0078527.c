source_config_constructed (GObject *object)
{
	ESourceConfig *config;
	ESourceRegistry *registry;
	ESource *original_source;
	ESource *collection_source = NULL;

	config = E_SOURCE_CONFIG (object);
	registry = e_source_config_get_registry (config);
	original_source = e_source_config_get_original_source (config);


	if (original_source != NULL) {
		const gchar *extension_name;

		extension_name = E_SOURCE_EXTENSION_COLLECTION;
		collection_source = e_source_registry_find_extension (
			registry, original_source, extension_name);
		config->priv->collection_source = collection_source;
	}

	if (original_source != NULL)
		e_source_config_insert_widget (
			config, NULL, _("Type:"),
			config->priv->type_label);
	else
		e_source_config_insert_widget (
			config, NULL, _("Type:"),
			config->priv->type_combo);


	if (collection_source != NULL)
		e_source_config_insert_widget (
			config, NULL, _("Name:"),
			config->priv->name_label);
	else
		e_source_config_insert_widget (
			config, NULL, _("Name:"),
			config->priv->name_entry);

	source_config_init_backends (config);
}
