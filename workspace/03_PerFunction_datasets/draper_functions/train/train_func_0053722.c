gnc_tree_model_account_finalize (GObject *object)
{
    GncTreeModelAccountPrivate *priv;
    GncTreeModelAccount *model;

    g_return_if_fail (object != NULL);
    g_return_if_fail (GNC_IS_TREE_MODEL_ACCOUNT (object));

    ENTER("model %p", object);

    model = GNC_TREE_MODEL_ACCOUNT (object);
    priv = GNC_TREE_MODEL_ACCOUNT_GET_PRIVATE(model);

    priv->book = NULL;

    if (G_OBJECT_CLASS (parent_class)->finalize)
        G_OBJECT_CLASS(parent_class)->finalize (object);
    LEAVE(" ");
}
