gnc_account_sel_purge_account( GNCAccountSel *gas,
                               Account *target,
                               gboolean recursive)
{
    GtkTreeModel *model = GTK_TREE_MODEL(gas->store);
    GtkTreeIter iter;
    Account *acc;
    gboolean more;

    if (!gtk_tree_model_get_iter_first(model, &iter))
        return;

    if (!recursive)
    {
        do
        {
            gtk_tree_model_get(model, &iter, ACCT_COL_PTR, &acc, -1);
            if (acc == target)
            {
                gtk_list_store_remove(gas->store, &iter);
                break;
            }
        }
        while (gtk_tree_model_iter_next(model, &iter));
    }
    else
    {
        do
        {
            gtk_tree_model_get(model, &iter, ACCT_COL_PTR, &acc, -1);
            while (acc)
            {
                if (acc == target)
                    break;
                acc = gnc_account_get_parent(acc);
            }

            if (acc == target)
                more = gtk_list_store_remove(gas->store, &iter);
            else
                more = gtk_tree_model_iter_next(model, &iter);
        }
        while (more);
    }

    gtk_combo_box_set_active(GTK_COMBO_BOX(gas->combo), 0);
}
