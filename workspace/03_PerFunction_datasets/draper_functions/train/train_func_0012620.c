make_icon (GtkAction *a, GtkWidget *tool)
{
	GtkIconSize size;
	gint pixels = 8;
	char *stock_id;
	GdkPixbuf *icon;
	GtkSettings *settings = gtk_widget_get_settings (tool);
	GdkScreen *screen = gtk_widget_get_screen (tool);

	g_object_get (a, "stock-id", &stock_id, NULL);
	if (stock_id == NULL)
		return NULL;
	if (GO_IS_TOOL_COMBO_COLOR (tool)) {
		GtkWidget *parent = gtk_widget_get_parent (tool);
		if (parent)
			size = gtk_toolbar_get_icon_size (GTK_TOOLBAR (parent));
		else
			g_object_get (settings,
					  "gtk-toolbar-icon-size", &size,
					  NULL);
		gtk_icon_size_lookup_for_settings (settings, size,
						   &pixels, NULL);
	} else
		size = GTK_ICON_SIZE_MENU;
	icon = gtk_icon_theme_load_icon
		(gtk_icon_theme_get_for_screen (screen),
		 stock_id, pixels, 0, NULL);
	g_free (stock_id);

	return icon;
}
