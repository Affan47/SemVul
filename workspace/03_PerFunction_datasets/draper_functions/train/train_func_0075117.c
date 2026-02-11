panel_icon_chooser_set_fallback_icon_name (PanelIconChooser *chooser,
					   const char       *fallback_icon_name)
{
	g_return_if_fail (PANEL_IS_ICON_CHOOSER (chooser));

	if (g_strcmp0 (chooser->priv->fallback_icon_name, fallback_icon_name) == 0)
		return;

	if (chooser->priv->fallback_icon_name)
		g_free (chooser->priv->fallback_icon_name);
	chooser->priv->fallback_icon_name = g_strdup (fallback_icon_name);

	_panel_icon_chooser_update (chooser);

	g_object_notify (G_OBJECT (chooser), "fallback-icon-name");
}
