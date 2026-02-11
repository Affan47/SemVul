mnu_menu_popup(const MenuInfo *mi, const gchar *name, GtkMenuPositionFunc pos, gpointer data, guint button, guint32 activate_time)
{
	GtkWidget	*menu;

	if((menu = mnu_menu_widget_get(mi, name)) != NULL)
	{
		g_signal_connect_after(G_OBJECT(menu), "hide", G_CALLBACK(evt_popup_hide), NULL);
		g_signal_connect(G_OBJECT(menu), "destroy_event", G_CALLBACK(evt_popup_destroy), NULL);
		gtk_menu_popup(GTK_MENU(menu), NULL, NULL, pos, data, button, activate_time);

	}
	return menu != NULL;
}
