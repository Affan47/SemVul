bet_array_update_average_column ( GtkTreeModel *model,
                        GtkTreePath *path,
                        GtkTreeIter *iter,
                        gpointer data )
{
    gchar *str_balance = NULL;
    gchar *tmp_str;
    gchar *color_str = NULL;
    gint selected_account;
    gboolean select = FALSE;
    SBR *tmp_range = (SBR*) data;
    gsb_real amount;

    if ( tmp_range -> first_pass )
    {
        tmp_range -> first_pass = FALSE;
        return FALSE;
    }

    gtk_tree_model_get ( model, iter, SPP_ESTIMATE_TREE_SELECT_COLUMN, &select, -1 );
    if ( select )
    {
        gtk_tree_store_set ( GTK_TREE_STORE ( model ),
                        iter,
                        SPP_ESTIMATE_TREE_BALANCE_COLUMN, "",
                        -1 );

        return FALSE;
    }

    selected_account = gsb_gui_navigation_get_current_account ( );
    if ( selected_account == -1 )
        return FALSE;

    gtk_tree_model_get ( model, iter, SPP_ESTIMATE_TREE_AMOUNT_COLUMN, &tmp_str, -1 );

    amount = gsb_real_safe_real_from_string ( tmp_str );

    tmp_range -> current_balance = gsb_real_add ( tmp_range -> current_balance, amount );
    str_balance = gsb_real_get_string_with_currency ( tmp_range -> current_balance,
                                gsb_data_account_get_currency ( selected_account ), TRUE );

    if ( tmp_range->current_balance.mantissa < 0 )
        color_str = "red";
    else
        color_str = NULL;

    gtk_tree_store_set ( GTK_TREE_STORE ( model ),
                        iter,
                        SPP_ESTIMATE_TREE_BALANCE_COLUMN, str_balance,
                        SPP_ESTIMATE_TREE_BALANCE_COLOR, color_str,
                        -1 );
    g_free ( str_balance );

    return FALSE;
}
