on_share_nfs_delete_clicked (GtkWidget *widget, gpointer data)
{
	GtkWidget        *table;
	GtkTreeSelection *selection;
	GtkTreeIter       iter;
	GtkTreeModel     *model;

	table = gst_dialog_get_widget (tool->main_dialog, "share_nfs_acl");
	selection = gtk_tree_view_get_selection (GTK_TREE_VIEW (table));

	if (gtk_tree_selection_get_selected (selection, &model, &iter))
		gtk_list_store_remove (GTK_LIST_STORE (model), &iter);
}
