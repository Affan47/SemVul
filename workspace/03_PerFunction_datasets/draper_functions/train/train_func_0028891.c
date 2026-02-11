gnc_tree_model_account_types_iter_nth_child (GtkTreeModel * tree_model,
        GtkTreeIter * iter,
        GtkTreeIter * parent, int n)
{
    GncTreeModelAccountTypes *model;

    g_return_val_if_fail (GNC_IS_TREE_MODEL_ACCOUNT_TYPES (tree_model), FALSE);

    if (parent != NULL)
        return FALSE;

    model = GNC_TREE_MODEL_ACCOUNT_TYPES (tree_model);

    if (n > ACCT_TYPE_NONE && n < NUM_ACCOUNT_TYPES)
    {
        iter->stamp = model->stamp;
        iter->user_data = GINT_TO_POINTER (n);
        return TRUE;
    }

    iter->stamp = 0;
    return FALSE;
}
