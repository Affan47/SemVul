cursor_changed_cb (GtkTreeView *view,
		   gpointer     data)
{
	BraseroPlugin *plugin;
	BraseroPluginManagerUI *pm = data;
	BraseroPluginManagerUIPrivate *priv;

	priv = BRASERO_PLUGIN_MANAGER_UI_GET_PRIVATE (pm);
	plugin = plugin_manager_ui_get_selected_plugin (pm);

	gtk_widget_set_sensitive (GTK_WIDGET (priv->about_button),
				  plugin != NULL);
	gtk_widget_set_sensitive (GTK_WIDGET (priv->configure_button),
				  (plugin != NULL) &&
				   brasero_plugin_get_next_conf_option (plugin, NULL));
}
