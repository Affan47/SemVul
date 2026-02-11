recent_chooser_item_activated (GtkRecentChooser *chooser,
			       GeditWindow      *window)
{
	GFile *location;
	gchar *uri;


	uri = gtk_recent_chooser_get_current_uri (chooser);
	location = g_file_new_for_uri (uri);

	if (location)
	{
		open_recent_file (location, window);
		g_object_unref (location);
	}

	g_free (uri);
}
