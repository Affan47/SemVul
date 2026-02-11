devhelp_plugin_toggle_sidebar_tab(DevhelpPlugin *self, gint tab)
{
	GtkNotebook *sbar_nb;
	gint current_tab_id;

	g_return_if_fail(self != NULL);

	sbar_nb = GTK_NOTEBOOK(geany->main_widgets->sidebar_notebook);
	current_tab_id = gtk_notebook_get_current_page(sbar_nb);

	if (current_tab_id == gtk_notebook_page_num(sbar_nb, self->priv->sb_notebook))
		gtk_notebook_set_current_page(sbar_nb, self->priv->last_sb_tab_id);
	else
	{
		if (tab == 0)
			devhelp_plugin_activate_contents_tab(self);
		else if (tab == 1)
			devhelp_plugin_activate_search_tab(self);
		else
			g_warning("Can't toggle to unknown tab ID: %d", tab);
	}
}
