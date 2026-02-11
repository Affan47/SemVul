scrollToIter( GtkTreeView* tv, GtkTreeIter* iter, int colnum, gboolean start_editing )
{
    GtkTreeModel*      model = gtk_tree_view_get_model( tv );
    GtkTreePath*       path = 0;
    GtkTreeViewColumn* focus_column = 0;
    if( colnum >= 0 )
    {
        focus_column = gtk_tree_view_get_column( tv, colnum );
    }
    path = gtk_tree_model_get_path( model, iter );
    gtk_tree_view_set_cursor( tv, path, focus_column, start_editing );
    gtk_tree_path_free( path );
}
