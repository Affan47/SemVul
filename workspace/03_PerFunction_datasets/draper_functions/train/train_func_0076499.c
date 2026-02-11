cm_menu_set_sensitive_full(GtkUIManager *gui_manager, const gchar *menu, gboolean sensitive)
{
	GtkWidget *widget;
	gchar *path = g_strdup_printf("/%s/", menu);

	widget = gtk_ui_manager_get_widget(gui_manager, path);
	if( !GTK_IS_WIDGET(widget) ) {
		g_message("Blah, '%s' is not a widget.\n", path);
	}

	if( !GTK_IS_MENU_ITEM(widget) ) {
		g_message("Blah, '%s' is not a menu item.\n", path);
	}

	gtk_widget_set_sensitive(widget, sensitive);
	g_free(path);
}
