open_policy_on_remove_click(GtkButton * button __attribute__ ((unused)), gpointer user_data)
{
	struct open_policy *op = (struct open_policy *)user_data;
	GtkTreeSelection *selection = gtk_tree_view_get_selection(op->module_view);
	GtkTreeIter iter;
	char *path;
	if (!gtk_tree_selection_get_selected(selection, NULL, &iter)) {
		return;
	}
	gtk_tree_model_get(GTK_TREE_MODEL(op->module_store), &iter, 0, &path, -1);
	gtk_list_store_remove(op->module_store, &iter);
}
