gnc_tree_model_split_reg_iter_n_children (GtkTreeModel *tree_model, GtkTreeIter *iter)
{


    GncTreeModelSplitReg *model = GNC_TREE_MODEL_SPLIT_REG (tree_model);
    GList *tnode;
    int i;

    g_return_val_if_fail (GNC_IS_TREE_MODEL_SPLIT_REG (tree_model), FALSE);
    ENTER("model %p, iter %s", tree_model, iter_to_string (iter));

    if (iter == NULL) {
        i = g_list_length (model->priv->tlist);
        LEAVE ("toplevel count is %d", i);
        return i;
    }

    if (IS_SPLIT (iter))
        i = 0;

    if (IS_TROW1 (iter))
        i = 1;

    if (IS_TROW2 (iter))
    {
        tnode = iter->user_data2;
        i = xaccTransCountSplits (tnode->data);
        if (tnode == model->priv->bsplit_parent_node)
            i++;
    }

    LEAVE ("The number of children iter has is %d", i);
    return i;
}
