panel_context_menu_setup_delete_panel_item (GtkWidget *menu,
					    GtkWidget *menuitem)
{
	PanelWidget *panel_widget;
	gboolean     sensitive;

	panel_context_menu_check_for_screen (NULL, NULL, NULL);

	panel_widget = menu_get_panel (menu);

	g_assert (PANEL_IS_TOPLEVEL (panel_widget->toplevel));

	sensitive =
		!panel_toplevel_is_last (panel_widget->toplevel) &&
		!panel_lockdown_get_panels_locked_down_s () &&
		panel_layout_is_writable ();

	gtk_widget_set_sensitive (menuitem, sensitive);
}
