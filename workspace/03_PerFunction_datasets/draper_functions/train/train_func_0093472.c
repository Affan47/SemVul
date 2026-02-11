set_no_data_visible (gboolean			visible,
		     gboolean			show_buttons,
		     TotemChaptersPlugin	*plugin)
{
	g_return_if_fail (TOTEM_IS_CHAPTERS_PLUGIN (plugin));

	if (visible) {
		gtk_widget_hide (plugin->priv->list_box);
		gtk_widget_show (plugin->priv->load_box);
	} else {
		gtk_widget_hide (plugin->priv->load_box);
		gtk_widget_show (plugin->priv->list_box);
	}

	gtk_widget_set_sensitive (plugin->priv->add_button, !visible);
	gtk_widget_set_sensitive (plugin->priv->tree, !visible);

	gtk_widget_set_visible (plugin->priv->load_button, show_buttons);
	gtk_widget_set_visible (plugin->priv->continue_button, show_buttons);
}
