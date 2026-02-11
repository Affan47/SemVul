tax_table_entries_refresh (TaxTableWindow *ttw)
{
    GList *list, *node;
    GtkTreeView *view;
    GtkListStore *store;
    GtkTreeIter iter;
    GtkTreePath *path;
    GtkTreeSelection *selection;
    GtkTreeRowReference *reference = NULL;
    GncTaxTableEntry *selected_entry;

    g_return_if_fail (ttw);

    view = GTK_TREE_VIEW (ttw->entries_view);
    store = GTK_LIST_STORE(gtk_tree_view_get_model(view));


    selected_entry = ttw->current_entry;
    gtk_list_store_clear (store);
    if (ttw->current_table == NULL)
        return;


    list = gncTaxTableGetEntries (ttw->current_table);
    if (list)
        list = g_list_reverse (g_list_copy (list));

    for (node = list ; node; node = node->next)
    {
        char *row_text[3];
        GncTaxTableEntry *entry = node->data;
        Account *acc = gncTaxTableEntryGetAccount (entry);
        gnc_numeric amount = gncTaxTableEntryGetAmount (entry);

        row_text[0] = gnc_account_get_full_name (acc);
        switch (gncTaxTableEntryGetType (entry))
        {
        case GNC_AMT_TYPE_PERCENT:
            row_text[1] =
                g_strdup_printf ("%s%%",
                                 xaccPrintAmount (amount,
                                                  gnc_default_print_info (FALSE)));
            break;
        default:
            row_text[1] =
                g_strdup_printf ("%s",
                                 xaccPrintAmount (amount,
                                                  gnc_default_print_info (TRUE)));
            break;
        }

        gtk_list_store_prepend(store, &iter);
        gtk_list_store_set(store, &iter,
                           TAX_ENTRY_COL_NAME, row_text[0],
                           TAX_ENTRY_COL_POINTER, entry,
                           TAX_ENTRY_COL_AMOUNT, row_text[1],
                           -1);
        if (entry == selected_entry)
        {
            path = gtk_tree_model_get_path(GTK_TREE_MODEL(store), &iter);
            reference = gtk_tree_row_reference_new(GTK_TREE_MODEL(store), path);
            gtk_tree_path_free(path);
        }

        g_free (row_text[0]);
        g_free (row_text[1]);
    }

    if (reference)
    {
        path = gtk_tree_row_reference_get_path(reference);
        gtk_tree_row_reference_free(reference);
        if (path)
        {
            selection = gtk_tree_view_get_selection(view);
            gtk_tree_selection_select_path(selection, path);
            gtk_tree_view_scroll_to_cell(view, path, NULL, TRUE, 0.5, 0.0);
            gtk_tree_path_free(path);
        }
    }
}
