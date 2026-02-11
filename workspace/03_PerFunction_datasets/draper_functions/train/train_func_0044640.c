gedit_panel_get_active (GeditPanel *panel)
{
	gint current;

	g_return_val_if_fail (GEDIT_IS_PANEL (panel), NULL);

	current = gtk_notebook_get_current_page (GTK_NOTEBOOK (panel->priv->notebook));

	if (current == -1)
	{
		return NULL;
	}

	return gtk_notebook_get_nth_page (GTK_NOTEBOOK (panel->priv->notebook), current);
}
