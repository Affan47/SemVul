gnc_account_sel_find_account (GtkTreeModel *model,
                              GtkTreePath *path,
                              GtkTreeIter *iter,
                              gas_find_data *data)
{
    Account *model_acc;

    gtk_tree_model_get(model, iter, ACCT_COL_PTR, &model_acc, -1);
    if (data->acct != model_acc)
        return FALSE;

    gtk_combo_box_set_active_iter(GTK_COMBO_BOX(data->gas->combo), iter);
    return TRUE;
}
