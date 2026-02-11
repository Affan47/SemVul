message_add_filter_cb (GeditMessageBus *bus,
                       GeditMessage    *message,
                       GeditWindow     *window)
{
	const gchar *object_path = NULL;
	const gchar *method = NULL;
	gulong id;
	GeditMessage *cbmessage;
	FilterData *filter_data;
	WindowData *data;
	GType message_type;

	data = get_window_data (window);

	object_path = gedit_message_get_object_path (message);
	method = gedit_message_get_method (message);

	message_type = gedit_message_bus_lookup (bus, object_path, method);

	if (message_type == G_TYPE_INVALID)
	{
		return;
	}


	if (!gedit_message_type_check (message_type, "id", G_TYPE_STRING) ||
	    !gedit_message_type_check (message_type, "location", G_TYPE_FILE) ||
	    !gedit_message_type_check (message_type, "is-directory", G_TYPE_BOOLEAN) ||
	    !gedit_message_type_check (message_type, "filter", G_TYPE_BOOLEAN))
	{
		return;
	}

	cbmessage = g_object_new (message_type,
	                          "object-path", object_path,
	                          "method", method,
	                          "id", NULL,
	                          "location", NULL,
	                          "is-directory", FALSE,
	                          "filter", FALSE,
	                          NULL);


	filter_data = filter_data_new (window, cbmessage);

	id = gedit_file_browser_widget_add_filter (data->widget,
	                                           (GeditFileBrowserWidgetFilterFunc)custom_message_filter_func,
	                                           filter_data,
	                                           (GDestroyNotify)filter_data_free);

	filter_data->id = id;
}
