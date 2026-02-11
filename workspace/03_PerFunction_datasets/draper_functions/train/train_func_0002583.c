address_completion_unregister_entry(GtkEntry *entry)
{
	GObject *entry_obj;

	cm_return_if_fail(entry != NULL);
	cm_return_if_fail(GTK_IS_ENTRY(entry));

	entry_obj = g_object_get_data(G_OBJECT(entry), ENTRY_DATA_TAB_HOOK);
	cm_return_if_fail(entry_obj);
	cm_return_if_fail(G_OBJECT(entry_obj) == G_OBJECT(entry));


	g_object_set_data(G_OBJECT(entry), ENTRY_DATA_TAB_HOOK, NULL);


	g_signal_handlers_disconnect_by_func(G_OBJECT(entry),
			G_CALLBACK(address_completion_entry_key_pressed),
			COMPLETION_UNIQUE_DATA);
}
