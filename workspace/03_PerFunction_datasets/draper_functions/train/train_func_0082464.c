evt_sview_remove_clicked(GtkWidget *wid, gpointer user)
{
	PDef		*def = user;
	GtkTreeIter	iter;

	if(gtk_tree_selection_get_selected(gtk_tree_view_get_selection(GTK_TREE_VIEW(def->sview)), NULL, &iter))
	{
		guint	i;

		for(i = def->srow; i < def->edit.num_columns - 1; i++)
			def->edit.format[i] = def->edit.format[i + 1];
		def->edit.num_columns--;
		gtk_list_store_remove(def->sstore, &iter);
	}
}
