metatree_get_row_type_from_tree_view ( GtkWidget *tree_view )
{
    GtkTreeSelection *selection;
    GtkTreeModel *model;
    GtkTreeIter iter;
    enum meta_tree_row_type type_division;

    selection = gtk_tree_view_get_selection ( GTK_TREE_VIEW ( tree_view ) );
    if ( selection && gtk_tree_selection_get_selected ( selection, &model, &iter ) )
    {
        GtkTreePath *path;
        GtkTreeIter parent;
        gint no_division = 0;
        gint no_sub_division = 0;

        gtk_tree_model_get ( model, &iter,
                        META_TREE_NO_DIV_COLUMN, &no_division,
                        META_TREE_NO_SUB_DIV_COLUMN, &no_sub_division,
                        -1 );

        if ( no_sub_division == 0
         &&
         gtk_tree_model_iter_parent ( GTK_TREE_MODEL ( model ), &parent, &iter ) )
        {
            gint nbre_trans_s_s_div = 0;

            nbre_trans_s_s_div = metatree_get_nbre_transactions_sans_sub_div ( tree_view );
            if ( nbre_trans_s_s_div > 0 )
                return META_TREE_TRANS_S_S_DIV;
            else
                return META_TREE_INVALID;
        }

        path = gtk_tree_model_get_path ( model, &iter );
        type_division = metatree_get_row_type ( model, path );

        gtk_tree_path_free ( path );

        return type_division;
    }

    return META_TREE_INVALID;
}
