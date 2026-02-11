gtm_sr_make_new_blank_split (GncTreeModelSplitReg *model)
{
    GtkTreeIter iter;
    Split *split;
    GList *tnode = model->priv->bsplit_parent_node;

    ENTER("");

    split = xaccMallocSplit (model->priv->book);
    model->priv->bsplit = split;
    model->priv->bsplit_node->data = model->priv->bsplit;

    DEBUG("make new blank split %p and insert at trans %p", split, tnode->data);


    iter = gtm_sr_make_iter (model, BLANK|SPLIT, tnode, model->priv->bsplit_node);
    gtm_sr_insert_row_at (model, &iter);
    LEAVE("");
}
