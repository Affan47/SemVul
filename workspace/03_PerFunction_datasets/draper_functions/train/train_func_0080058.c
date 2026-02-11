set_window (GeditDocumentsPanel *panel,
	    GeditWindow         *window)
{
	gedit_debug (DEBUG_PANEL);

	g_return_if_fail (panel->priv->window == NULL);
	g_return_if_fail (GEDIT_IS_WINDOW (window));

	panel->priv->window = g_object_ref (window);
	panel->priv->mnb = GEDIT_MULTI_NOTEBOOK (_gedit_window_get_multi_notebook (window));

	g_signal_connect (panel->priv->mnb,
			  "notebook-removed",
			  G_CALLBACK (multi_notebook_notebook_removed),
			  panel);
	g_signal_connect (panel->priv->mnb,
			  "tab-added",
			  G_CALLBACK (multi_notebook_tab_added),
			  panel);
	g_signal_connect (panel->priv->mnb,
			  "tab-removed",
			  G_CALLBACK (multi_notebook_tab_removed),
			  panel);
	g_signal_connect (panel->priv->mnb,
			  "page-reordered",
			  G_CALLBACK (multi_notebook_tabs_reordered),
			  panel);
	g_signal_connect (panel->priv->mnb,
			  "switch-tab",
			  G_CALLBACK (multi_notebook_tab_switched),
			  panel);

	refresh_list (panel);
}
