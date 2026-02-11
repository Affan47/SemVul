gnc_tree_model_commodity_iter_is_namespace (GncTreeModelCommodity *model,
        GtkTreeIter *iter)
{
    g_return_val_if_fail (GNC_IS_TREE_MODEL_COMMODITY (model), FALSE);
    g_return_val_if_fail (iter != NULL, FALSE);
    g_return_val_if_fail (iter->user_data != NULL, FALSE);
    g_return_val_if_fail (iter->stamp == model->stamp, FALSE);

    return (iter->user_data == ITER_IS_NAMESPACE);
}
