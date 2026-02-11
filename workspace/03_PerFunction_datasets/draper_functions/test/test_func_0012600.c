get_extension_menus (NautilusWindow *window)
{
	NautilusFile *file;
	NautilusWindowSlot *slot;
	GList *providers;
	GList *items;
	GList *l;

	providers = nautilus_module_get_extensions_for_type (NAUTILUS_TYPE_MENU_PROVIDER);
	items = NULL;

	slot = nautilus_window_get_active_slot (window);
	file = nautilus_window_slot_get_file (slot);

	for (l = providers; l != NULL; l = l->next) {
		NautilusMenuProvider *provider;
		GList *file_items;

		provider = NAUTILUS_MENU_PROVIDER (l->data);
		file_items = nautilus_menu_provider_get_background_items (provider,
									  GTK_WIDGET (window),
									  file);
		items = g_list_concat (items, file_items);
	}

	nautilus_module_extension_list_free (providers);

	return items;
}
