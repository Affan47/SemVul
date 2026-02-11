payee_list_button_press ( GtkWidget *tree_view,
                        GdkEventButton *ev,
                        gpointer null )
{
    if ( ev -> type == GDK_2BUTTON_PRESS )
    {
        GtkTreeSelection *selection;
        GtkTreeModel *model;
        GtkTreeIter iter;
        GtkTreePath *path = NULL;
        enum meta_tree_row_type type_division;

        type_division = metatree_get_row_type_from_tree_view ( tree_view );
        if ( type_division == META_TREE_TRANSACTION )
            return FALSE;

        selection = gtk_tree_view_get_selection ( GTK_TREE_VIEW ( tree_view ) );
        if ( selection && gtk_tree_selection_get_selected (selection, &model, &iter ) )
            path = gtk_tree_model_get_path  ( model, &iter);

        if ( conf.metatree_action_2button_press == 1 )
        {
            edit_payee ( GTK_TREE_VIEW ( tree_view ) );

            gtk_tree_path_free ( path );
            return TRUE;
        }
        else
        {
            if ( gtk_tree_view_row_expanded ( GTK_TREE_VIEW ( tree_view ), path ) )
                gtk_tree_view_collapse_row ( GTK_TREE_VIEW ( tree_view ), path );
            else
                gtk_tree_view_expand_row ( GTK_TREE_VIEW ( tree_view ), path, FALSE );

            gtk_tree_path_free ( path );
            return FALSE;
        }

        return TRUE;
    }
    else
        return FALSE;
}
