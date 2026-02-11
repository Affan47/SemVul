_gth_browser_set_statusbar_visibility (GthBrowser *browser,
				       gboolean    visible)
{
	g_return_if_fail (browser != NULL);

	_gth_browser_set_action_active (browser, "View_Statusbar", visible);
	if (visible)
		gtk_widget_show (browser->priv->statusbar);
	else
		gtk_widget_hide (browser->priv->statusbar);
}
