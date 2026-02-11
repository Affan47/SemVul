set_busy (GeditFileBrowserWidget *obj,
	  gboolean                busy)
{
	GdkCursor *cursor;
	GdkWindow *window;

	window = gtk_widget_get_window (GTK_WIDGET (obj->priv->treeview));

	if (!GDK_IS_WINDOW (window))
		return;

	if (busy)
	{
		cursor = gdk_cursor_new (GDK_WATCH);
		gdk_window_set_cursor (window, cursor);
		g_object_unref (cursor);
	}
	else
	{
		gdk_window_set_cursor (window, NULL);
	}
}
