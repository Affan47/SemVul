xaccCloneAccount(const Account *from, QofBook *book)
{
    Account *ret;
    AccountPrivate *from_priv, *priv;

    g_return_val_if_fail(GNC_IS_ACCOUNT(from), NULL);
    g_return_val_if_fail(QOF_IS_BOOK(book), NULL);

    ENTER (" ");
    ret = g_object_new (GNC_TYPE_ACCOUNT, NULL);
    g_return_val_if_fail (ret, NULL);

    from_priv = GET_PRIVATE(from);
    priv = GET_PRIVATE(ret);
    xaccInitAccount (ret, book);


    priv->type = from_priv->type;

    priv->accountName = CACHE_INSERT(from_priv->accountName);
    priv->accountCode = CACHE_INSERT(from_priv->accountCode);
    priv->description = CACHE_INSERT(from_priv->description);

    kvp_frame_delete(ret->inst.kvp_data);
    ret->inst.kvp_data = kvp_frame_copy(from->inst.kvp_data);


    priv->commodity = gnc_commodity_obtain_twin(from_priv->commodity, book);
    gnc_commodity_increment_usage_count(priv->commodity);

    priv->commodity_scu = from_priv->commodity_scu;
    priv->non_standard_scu = from_priv->non_standard_scu;

    qof_instance_set_dirty(&ret->inst);
    LEAVE (" ");
    return ret;
}
