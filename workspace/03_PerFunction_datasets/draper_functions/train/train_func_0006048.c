on_deletebutton_clicked(GtkButton *button, gpointer user_data)
{
	if (button){};

	GtkWidget *treeview = glade_xml_get_widget (((xyz_t *) user_data)->x, "treeview1");

	GtkTreeSelection *select = gtk_tree_view_get_selection(GTK_TREE_VIEW(treeview));
	gtk_tree_selection_set_mode(select, GTK_SELECTION_SINGLE);

	GtkTreeIter iter;
	GtkTreeModel *model = GTK_TREE_MODEL(((xyz_t *) user_data)->y);
	if (gtk_tree_selection_get_selected(select, &model, &iter))
		gtk_list_store_remove(GTK_LIST_STORE(model), &iter);
}
