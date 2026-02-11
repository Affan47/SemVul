show_tree_popup_menu (GtkTreeView        *tree,
		      BraseroPluginManagerUI *pm,
		      GdkEventButton     *event)
{
	BraseroPluginManagerUIPrivate *priv;

	priv = BRASERO_PLUGIN_MANAGER_UI_GET_PRIVATE (pm);

	if (priv->popup_menu)
		gtk_widget_destroy (priv->popup_menu);

	priv->popup_menu = create_tree_popup_menu (pm);
	if (!priv->popup_menu)
		return;

	gtk_menu_attach_to_widget (GTK_MENU (priv->popup_menu),
				   GTK_WIDGET (pm),
				   (GtkMenuDetachFunc) tree_popup_menu_detach);

	if (event != NULL)
	{
		gtk_menu_popup (GTK_MENU (priv->popup_menu), NULL, NULL,
				NULL, NULL,
				event->button, event->time);
	}
	else
	{
		gtk_menu_popup (GTK_MENU (priv->popup_menu), NULL, NULL,
				menu_position_under_tree_view, tree,
				0, gtk_get_current_event_time ());

		gtk_menu_shell_select_first (GTK_MENU_SHELL (priv->popup_menu),
					     FALSE);
	}
}
