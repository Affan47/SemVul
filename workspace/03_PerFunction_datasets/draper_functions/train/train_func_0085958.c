slot_add_extension_extra_widgets (NemoWindowSlot *slot)
{
	GList *providers, *l;
	GtkWidget *widget;
	char *uri;
	NemoWindow *window;

	providers = nemo_module_get_extensions_for_type (NEMO_TYPE_LOCATION_WIDGET_PROVIDER);
	window = nemo_window_slot_get_window (slot);

	uri = g_file_get_uri (slot->location);
	for (l = providers; l != NULL; l = l->next) {
		NemoLocationWidgetProvider *provider;

		provider = NEMO_LOCATION_WIDGET_PROVIDER (l->data);
		widget = nemo_location_widget_provider_get_widget (provider, uri, GTK_WIDGET (window));
		if (widget != NULL) {
			nemo_window_slot_add_extra_location_widget (slot, widget);
		}
	}
	g_free (uri);

	nemo_module_extension_list_free (providers);
}
