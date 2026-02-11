gth_browser_show_filterbar (GthBrowser *browser,
			    gboolean    show)
{
	if (show)
		gtk_widget_show (browser->priv->filterbar);
	else
		gtk_widget_hide (browser->priv->filterbar);
	_gth_browser_set_action_active (browser, "View_Filterbar", show);
	g_settings_set_boolean (browser->priv->browser_settings, PREF_BROWSER_FILTERBAR_VISIBLE, show);
}
