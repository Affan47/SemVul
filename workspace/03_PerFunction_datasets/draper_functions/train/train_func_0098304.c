gth_toggle_menu_action_create_tool_item (GtkAction *action)
{
	GthToggleMenuAction *self = GTH_TOGGLE_MENU_ACTION (action);
	GtkWidget           *tool_item;

	tool_item = g_object_new (GTH_TYPE_TOGGLE_MENU_TOOL_BUTTON,
				  "show-arrow", self->priv->show_arrow,
				  NULL);
	if (self->priv->show_menu_func != NULL)
		g_signal_connect (tool_item,
				  "show_menu",
				  G_CALLBACK (tool_item_show_menu_cb),
				  self);
	else if (self->priv->menu != NULL) {
		g_object_set (tool_item,
			      "menu", self->priv->menu,
			      "menu-halign", self->priv->menu_halign,
			      NULL);
	}

	return tool_item;
}
