ibus_bus_get_config (IBusBus *bus)
{
    g_assert (IBUS_IS_BUS (bus));
    g_return_val_if_fail (ibus_bus_is_connected (bus), NULL);

    IBusBusPrivate *priv;
    priv = IBUS_BUS_GET_PRIVATE (bus);

    if (priv->config == NULL && priv->connection) {
        priv->config = ibus_config_new (priv->connection, NULL, NULL);
        if (priv->config) {
            g_signal_connect (priv->config, "destroy", G_CALLBACK (_config_destroy_cb), bus);
        }
    }

    return priv->config;
}
