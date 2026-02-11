expert_edit_value (void)
{

	GtkTreeIter treeiter;
	Options *opts;
	Option *option;
	if (!expert_get_option (opts, option, treeiter))
		return;

	if (option->flags() & OPTFLG_USER_NO_CHANGE)
		return;


	GtkTreePath *path;
	path=gtk_tree_model_get_path (GTK_TREE_MODEL(expert_liststore), &treeiter);
	gtk_tree_view_set_cursor (expert_treeview, path, expert_col_value, true);
	gtk_widget_grab_focus (GTK_WIDGET (expert_treeview));
	gtk_tree_path_free (path);
}
