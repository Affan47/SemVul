_e2_toolbar_menu_popup (GtkWidget *button,
	gint x, gint y, gint mouse_button, guint32 time, E2_ToolbarRuntime *rt)
{
	GtkWidget *menu = g_object_get_data (G_OBJECT (button), "menu");
	if (menu == NULL)
	{
		if (rt != NULL)
			menu = _e2_toolbar_createrest_menu (rt);
		else
			return FALSE;
	}

	gtk_menu_popup (GTK_MENU (menu), NULL, NULL,
		(GtkMenuPositionFunc) e2_toolbar_set_menu_position, button, mouse_button, time);

	return FALSE;
}
