directory_cell_edited(GtkCellRendererText *cell,
			   gchar *path_string,
			   gchar *new_text,
			   struct w *widgets)
{

    GtkTreeIter iter;
    GtkTreePath *path = NULL;

    path = gtk_tree_path_new_from_string(path_string);
    gtk_tree_model_get_iter(GTK_TREE_MODEL(widgets->directory_store), &iter, path);

    if( path!=NULL )
      gtk_tree_path_free(path);

    gtk_list_store_set(GTK_LIST_STORE(widgets->directory_store), &iter, 0, new_text, -1);
}
