setup_plugins_page (GeditPreferencesDialog *dlg)
{
	GtkWidget *page_content;

	gedit_debug (DEBUG_PREFS);

	page_content = peas_gtk_plugin_manager_new (NULL);
	gtk_widget_set_vexpand (GTK_WIDGET (page_content), TRUE);
	gtk_widget_set_hexpand (GTK_WIDGET (page_content), TRUE);
	g_return_if_fail (page_content != NULL);

	gtk_container_add (GTK_CONTAINER (dlg->priv->plugin_manager_place_holder),
	                   page_content);

	gtk_widget_show_all (page_content);
}
