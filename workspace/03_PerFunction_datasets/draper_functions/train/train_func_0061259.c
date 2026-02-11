gnc_account_get_descendants (const Account *account)
{
    AccountPrivate *priv;
    GList *child, *descendants;

    g_return_val_if_fail(GNC_IS_ACCOUNT(account), NULL);

    priv = GET_PRIVATE(account);
    if (!priv->children)
        return NULL;

    descendants = NULL;
    for (child = priv->children; child; child = g_list_next(child))
    {
        descendants = g_list_append(descendants, child->data);
        descendants = g_list_concat(descendants,
                                    gnc_account_get_descendants(child->data));
    }
    return descendants;
}
