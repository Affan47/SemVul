on_pointer_mode_changed (GladeApp           *app,
			 GParamSpec         *pspec,
			 GladeWindow *window)
{
	window->priv->setting_pointer_mode = TRUE;

	if (glade_app_get_pointer_mode () == GLADE_POINTER_SELECT)
		gtk_toggle_tool_button_set_active (window->priv->selector_button, TRUE);
	else
		gtk_toggle_tool_button_set_active (window->priv->selector_button, FALSE);

	if (glade_app_get_pointer_mode () == GLADE_POINTER_DRAG_RESIZE)
		gtk_toggle_tool_button_set_active (window->priv->drag_resize_button, TRUE);
	else
		gtk_toggle_tool_button_set_active (window->priv->drag_resize_button, FALSE);

	window->priv->setting_pointer_mode = FALSE;
}
