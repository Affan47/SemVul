panel_menu_button_popup_menu (PanelMenuButton *button,
			      guint            n_button,
			      guint32          activate_time)
{
	GdkScreen *screen;

	g_return_if_fail (PANEL_IS_MENU_BUTTON (button));

	panel_menu_button_create_menu (button);

	panel_toplevel_push_autohide_disabler (button->priv->toplevel);

	button_widget_set_ignore_leave (BUTTON_WIDGET (button), TRUE);

	screen = gtk_window_get_screen (GTK_WINDOW (button->priv->toplevel));
	gtk_menu_set_screen (GTK_MENU (button->priv->menu), screen);

	gtk_menu_popup (GTK_MENU (button->priv->menu),
			NULL,
			NULL,
			(GtkMenuPositionFunc) panel_applet_position_menu,
			GTK_WIDGET (button),
			n_button,
			activate_time);
}
