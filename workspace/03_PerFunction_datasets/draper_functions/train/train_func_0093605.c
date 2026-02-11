file_list_row_activated (GtkTreeView       *tree_view,
                         GtkTreePath       *path,
                         GtkTreeViewColumn *column)
{
	GiggleFileListPriv *priv = GET_PRIV (tree_view);
	GtkAction          *action;

	action = gtk_ui_manager_get_action (priv->ui_manager, "/ui/PopupMenu/Edit");
	gtk_action_activate (action);

	if (GTK_TREE_VIEW_CLASS (giggle_file_list_parent_class)->row_activated)
		GTK_TREE_VIEW_CLASS (giggle_file_list_parent_class)->row_activated (tree_view, path, column);
}
