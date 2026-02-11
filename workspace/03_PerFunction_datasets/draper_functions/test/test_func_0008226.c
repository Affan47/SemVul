message_get_root_cb (GeditMessageBus *bus,
		     GeditMessage    *message,
		     WindowData      *data)
{
	GeditFileBrowserStore *store;
	GFile *location;

	store = gedit_file_browser_widget_get_browser_store (data->widget);
	location = gedit_file_browser_store_get_virtual_root (store);

	if (location)
	{
		g_object_set (message, "location", location, NULL);
		g_object_unref (location);
	}
}
