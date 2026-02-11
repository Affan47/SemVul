reload_plugin_function_list (	GtkWidget	*this_widget,
				KTPlugin	*plugin       )


{
	GtkCombo	*plugin_function_combo;
	GtkWidget	*plugin_function_combo_entry;
	GtkList		*plugin_function_list_widget;
	int		count;

	plugin_function_combo_entry = lookup_widget(this_widget, "plugin_function_comboentry");

	g_signal_handlers_block_by_func (GTK_OBJECT(plugin_function_combo_entry),
	                                  on_plugin_function_comboentry_changed, NULL);

	plugin_function_combo = GTK_COMBO(lookup_widget(this_widget, "plugin_function_combo"));

	plugin_function_list_widget = GTK_LIST(plugin_function_combo->list);

	gtk_list_clear_items (plugin_function_list_widget, 0, -1);

	if (plugin)
	{

		for (count = 0; count < plugin->num_functions; count++)
		{
			list_append_item (plugin_function_list_widget, plugin->function[count]);
		}
	}


	g_signal_handlers_unblock_by_func (GTK_OBJECT(plugin_function_combo_entry),
	                                    on_plugin_function_comboentry_changed, NULL);
}
