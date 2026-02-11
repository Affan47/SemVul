xaccAccountSetType (Account *acc, GNCAccountType tip)
{
    AccountPrivate *priv;


    g_return_if_fail(GNC_IS_ACCOUNT(acc));
    g_return_if_fail(tip < NUM_ACCOUNT_TYPES);


    priv = GET_PRIVATE(acc);
    if (priv->type == tip)
        return;

    xaccAccountBeginEdit(acc);
    priv->type = tip;
    priv->balance_dirty = TRUE;
    mark_account(acc);
    xaccAccountCommitEdit(acc);
}
