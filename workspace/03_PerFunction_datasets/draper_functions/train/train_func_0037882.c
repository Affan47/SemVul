panel_addto_dialog_free (PanelAddtoDialog *dialog)
{
	GSList *item;

	if (dialog->name_notify)
		g_signal_handler_disconnect (dialog->panel_widget->toplevel,
					     dialog->name_notify);
	dialog->name_notify = 0;

	if (dialog->search_text)
		g_free (dialog->search_text);
	dialog->search_text = NULL;

	if (dialog->applet_search_text)
		g_free (dialog->applet_search_text);
	dialog->applet_search_text = NULL;

	if (dialog->addto_dialog)
		gtk_widget_destroy (dialog->addto_dialog);
	dialog->addto_dialog = NULL;

	for (item = dialog->applet_list; item != NULL; item = item->next) {
		PanelAddtoItemInfo *applet;

		applet = (PanelAddtoItemInfo *) item->data;
		panel_addto_dialog_free_item_info (applet);
		g_free (applet);
	}
	g_slist_free (dialog->applet_list);

	panel_addto_dialog_free_application_list (dialog->application_list);
	panel_addto_dialog_free_application_list (dialog->settings_list);

	if (dialog->filter_applet_model)
		g_object_unref (dialog->filter_applet_model);
	dialog->filter_applet_model = NULL;

	if (dialog->applet_model)
		g_object_unref (dialog->applet_model);
	dialog->applet_model = NULL;

	if (dialog->filter_application_model)
		g_object_unref (dialog->filter_application_model);
	dialog->filter_application_model = NULL;

	if (dialog->application_model)
		g_object_unref (dialog->application_model);
	dialog->application_model = NULL;

	if (dialog->menu_tree)
		g_object_unref (dialog->menu_tree);
	dialog->menu_tree = NULL;

	g_free (dialog);
}
