panel_action_button_drag_data_get (GtkWidget          *widget,
				   GdkDragContext     *context,
				   GtkSelectionData   *selection_data,
				   guint               info,
				   guint               time)
{
	PanelActionButton *button;
	char              *drag_data;

	g_return_if_fail (PANEL_IS_ACTION_BUTTON (widget));

	button = PANEL_ACTION_BUTTON (widget);

	drag_data = g_strdup_printf ("ACTION:%s:%d",
				     gconf_enum_to_string (panel_action_type_map, button->priv->type),
				     panel_find_applet_index (widget));

	gtk_selection_data_set (
		selection_data, gtk_selection_data_get_target (selection_data),
		8, (guchar *) drag_data, strlen (drag_data));

	g_free (drag_data);
}
