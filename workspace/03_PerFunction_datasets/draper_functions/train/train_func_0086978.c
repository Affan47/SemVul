gsb_csv_export_tree_view_list_foreach_callback ( GtkTreeModel *model,
                        GtkTreePath *path,
                        GtkTreeIter *iter,
                        FILE *csv_file )
{
    GtkTreeView *tree_view;
    GList *list;
    GList *list_tmp;

    tree_view = g_object_get_data ( G_OBJECT ( model ), "tree_view" );
    list = gtk_tree_view_get_columns ( tree_view );
    list_tmp = list;

    while ( list_tmp )
    {
        GtkTreeViewColumn *col;
        gchar *text;
        gint col_num_model;
        GType col_type_model;

        col = list_tmp -> data;

        col_num_model = GPOINTER_TO_INT ( g_object_get_data ( G_OBJECT ( col ), "num_col_model" ) );
        col_type_model = gtk_tree_model_get_column_type ( model, col_num_model );


        if ( col_type_model == G_TYPE_STRING )
            gtk_tree_model_get ( model, iter, col_num_model, &text, -1 );
        else if ( col_type_model == G_TYPE_INT )
        {
            gint number;

            gtk_tree_model_get ( model, iter, col_num_model, &number, -1 );
            text = utils_str_itoa ( number );
        }
        else
            text = NULL;

        CSV_STR_FIELD ( csv_file, text );
        CSV_CLEAR_FIELD ( text );

        list_tmp  = list_tmp -> next;
    }

    CSV_END_RECORD( csv_file );

    return FALSE;
}
