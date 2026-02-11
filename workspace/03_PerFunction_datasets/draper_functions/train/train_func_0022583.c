dispose (GObject *object)
{
	NMConnectionList *list = NM_CONNECTION_LIST (object);

	if (list->dialog)
		gtk_widget_hide (list->dialog);

	if (list->gui)
		g_object_unref (list->gui);
	if (list->nm_client)
		g_object_unref (list->nm_client);

	if (list->settings)
		g_object_unref (list->settings);

	G_OBJECT_CLASS (nm_connection_list_parent_class)->dispose (object);
}
