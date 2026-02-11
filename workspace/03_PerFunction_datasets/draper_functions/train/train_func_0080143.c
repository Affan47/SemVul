panel_menu_button_clicked (GtkButton *gtk_button)
{
	PanelMenuButton *button;
	GdkEvent        *event;

	g_return_if_fail (PANEL_IS_MENU_BUTTON (gtk_button));

	button = PANEL_MENU_BUTTON (gtk_button);

	if (GTK_BUTTON_CLASS (panel_menu_button_parent_class)->clicked)
		GTK_BUTTON_CLASS (panel_menu_button_parent_class)->clicked (gtk_button);

	if ((event = gtk_get_current_event ())) {
		panel_menu_button_popup_menu (button,
					      event->button.button,
					      event->button.time);
		gdk_event_free (event);
	} else {
		panel_menu_button_popup_menu (button, 1, GDK_CURRENT_TIME);
	}
}
