show_tab_popup_menu (GeditDocumentsPanel *panel,
		     GeditTab            *tab,
		     GdkEventButton      *event)
{
	GtkWidget *menu;

	gedit_debug (DEBUG_PANEL);

	menu = gedit_notebook_popup_menu_new (panel->priv->window, tab);

	if (event != NULL)
	{
		gtk_menu_popup (GTK_MENU (menu),
				NULL,
				NULL,
				NULL,
				NULL,
				event->button,
				event->time);
	}
	else
	{
		gtk_menu_popup (GTK_MENU (menu),
				NULL,
				NULL,
				(GtkMenuPositionFunc)menu_position,
				panel,
				0,
				gtk_get_current_event_time ());

		gtk_menu_shell_select_first (GTK_MENU_SHELL (menu), FALSE);
	}

	return TRUE;
}
