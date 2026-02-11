show_popup_menu (TotemChaptersPlugin	*plugin,
		 GdkEventButton		*event)
{
	guint			button = 0;
	guint32			_time;
	GtkTreePath		*path;
	gint			count;
	GtkWidget		*menu;
	GtkAction		*remove_act, *goto_act;
	GtkTreeSelection	*selection;

	g_return_val_if_fail (TOTEM_IS_CHAPTERS_PLUGIN (plugin), FALSE);

	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (plugin->priv->tree));

	if (event != NULL) {
		button = event->button;
		_time = event->time;

		if (gtk_tree_view_get_path_at_pos (GTK_TREE_VIEW (plugin->priv->tree),
						   event->x, event->y, &path, NULL, NULL, NULL)) {
			if (!gtk_tree_selection_path_is_selected (selection, path)) {
				gtk_tree_selection_unselect_all (selection);
				gtk_tree_selection_select_path (selection, path);
			}
			gtk_tree_path_free (path);
		} else
			gtk_tree_selection_unselect_all (selection);
	} else
		_time = gtk_get_current_event_time ();

	count = gtk_tree_selection_count_selected_rows (selection);

	if (count == 0)
		return FALSE;

	remove_act = gtk_action_group_get_action (plugin->priv->action_group, "remove");
	goto_act = gtk_action_group_get_action (plugin->priv->action_group, "goto");
	gtk_action_set_sensitive (remove_act, count > 0);
	gtk_action_set_sensitive (goto_act, count == 1);

	menu = gtk_ui_manager_get_widget (plugin->priv->ui_manager, "/totem-chapters-popup");

	gtk_menu_shell_select_first (GTK_MENU_SHELL (menu), FALSE);

	gtk_menu_popup (GTK_MENU (menu), NULL, NULL, NULL, NULL,
			button, _time);

	return TRUE;
}
