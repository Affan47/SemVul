gnc_tree_model_split_reg_get_parent (GncTreeModelSplitReg *model)
{
    GncTreeModelSplitRegPrivate *priv;
    GtkWidget *parent = NULL;

    priv = model->priv;

    if (priv->get_parent)
        parent = priv->get_parent (priv->user_data);

    return parent;
}
