gnc_tree_model_price_iter_n_children (GtkTreeModel *tree_model,
                                      GtkTreeIter *iter)
{
    GncTreeModelPrice *model;
    GncTreeModelPricePrivate *priv;
    gnc_commodity_table *ct;
    gnc_commodity_namespace *namespace;
    gnc_commodity *commodity;
    GList *list;
    gint n;

    g_return_val_if_fail (GNC_IS_TREE_MODEL_PRICE (tree_model), -1);

    model = GNC_TREE_MODEL_PRICE (tree_model);
    ENTER("model %p, iter %p (%s)", tree_model, iter,
          iter_to_string(model, iter));

    priv = GNC_TREE_MODEL_PRICE_GET_PRIVATE(model);
    if (iter == NULL)
    {
        ct = qof_book_get_data (priv->book, GNC_COMMODITY_TABLE);
        list = gnc_commodity_table_get_namespaces_list(ct);
        LEAVE("ns list length %d", g_list_length(list));
        return g_list_length (list);
    }

    if (iter->user_data == ITER_IS_NAMESPACE)
    {
        namespace = (gnc_commodity_namespace *)iter->user_data2;
        list = gnc_commodity_namespace_get_commodity_list(namespace);
        LEAVE("cm list length %d", g_list_length(list));
        return g_list_length (list);
    }

    if (iter->user_data == ITER_IS_COMMODITY)
    {
        commodity = (gnc_commodity *)iter->user_data2;
        list = gnc_pricedb_get_prices(priv->price_db, commodity, NULL);
        n = g_list_length(list);
        gnc_price_list_destroy(list);
        LEAVE("price list length %d", n);
        return n;
    }

    LEAVE("0");
    return 0;
}
