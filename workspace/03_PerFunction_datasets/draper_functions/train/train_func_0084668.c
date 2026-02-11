panel_menu_button_set_custom_icon (PanelMenuButton *button,
				   const char      *custom_icon)
{
	g_return_if_fail (PANEL_IS_MENU_BUTTON (button));

	g_free (button->priv->custom_icon);
	button->priv->custom_icon = NULL;

	if (custom_icon && custom_icon [0])
		button->priv->custom_icon = g_strdup (custom_icon);

	panel_menu_button_set_icon (button);
}
