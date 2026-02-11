gtk_combofix_get_first_string_from_sort_model ( GtkTreeModel *sort_model,
                        const gchar *string )
{
    GtkTreeIter iter;
    GtkTreeIter child_iter;
    gint length;
    gboolean separator = FALSE;
    gchar *model_string;
    gint model_string_length;

    length = strlen ( string );

    if ( gtk_tree_model_get_iter_first ( sort_model, &iter ) )
    {
        gtk_tree_model_get ( sort_model,
                        &iter,
                        COMBOFIX_COL_REAL_STRING, &model_string,
                        -1 );

        model_string_length = strlen ( model_string );

        if ( model_string_length >= length )
            return model_string;
        else if ( gtk_tree_model_iter_children ( sort_model, &child_iter, &iter ) )
        {
            gtk_tree_model_get ( sort_model,
                        &child_iter,
                        COMBOFIX_COL_REAL_STRING, &model_string,
                        COMBOFIX_COL_SEPARATOR, &separator,
                        -1 );
            return model_string;
        }
    }

    return g_strdup ( string );
}
