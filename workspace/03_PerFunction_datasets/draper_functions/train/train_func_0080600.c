x_authority_set_address (XAuthority *auth, const guint8 *address, gsize address_length)
{
    g_return_if_fail (auth != NULL);
    g_free (auth->priv->address);
    auth->priv->address = g_malloc (address_length);
    memcpy (auth->priv->address, address, address_length);
    auth->priv->address_length = address_length;
}
