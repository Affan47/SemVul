x_server_get_address (XServer *server)
{
    g_return_val_if_fail (server != NULL, NULL);

    if (!server->priv->address)
    {
        if (server->priv->hostname)
            server->priv->address = g_strdup_printf("%s:%d", server->priv->hostname, server->priv->number);
        else
            server->priv->address = g_strdup_printf(":%d", server->priv->number);
    }

    return server->priv->address;
}
