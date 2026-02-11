common_user_get_display_name (CommonUser *user)
{
    CommonUserPrivate *priv;

    g_return_val_if_fail (COMMON_IS_USER (user), NULL);

    priv = GET_USER_PRIVATE (user);
    if (!priv->real_name || strcmp (priv->real_name, "") == 0)
        return priv->name;
    else
        return priv->real_name;
}
