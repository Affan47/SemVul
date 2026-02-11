gtk_combofix_set_list ( GtkComboFix *combofix, GSList *list )
{
    GtkComboFixPrivate *priv = combofix -> priv;

    GSList *tmp_list;
    gint list_number = 0;
    gint length;
    GtkTreeIter iter;

    g_return_val_if_fail (combofix, FALSE );
    g_return_val_if_fail (GTK_IS_COMBOFIX (combofix), FALSE);
    g_return_val_if_fail (list, FALSE);

    gtk_tree_store_clear ( priv -> store );

    tmp_list = list;
    length = g_slist_length (list);

    while ( tmp_list )
    {
        gtk_combofix_fill_store ( combofix, tmp_list -> data, list_number );


        if (list_number < ( length-1 ) )
        {
            gtk_tree_store_append ( priv -> store, &iter, NULL );
            gtk_tree_store_set ( priv -> store,
                        &iter,
                        COMBOFIX_COL_LIST_NUMBER, list_number,
                        COMBOFIX_COL_SEPARATOR, TRUE,
                        -1 );
        }
        list_number++;

        tmp_list = tmp_list -> next;
    }

    return TRUE;
}
