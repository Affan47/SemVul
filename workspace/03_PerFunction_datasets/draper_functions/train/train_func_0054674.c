connect_host (GdlDockPlaceholder *ph,
              GdlDockObject      *new_host)
{
    if (ph->priv->host)
        disconnect_host (ph);

    ph->priv->host = new_host;
    g_object_weak_ref (G_OBJECT (ph->priv->host),
                       gdl_dock_placeholder_weak_notify, ph);

    ph->priv->host_detach_handler =
        g_signal_connect (ph->priv->host,
                          "detach",
                          (GCallback) detach_cb,
                          (gpointer) ph);

    ph->priv->host_dock_handler =
        g_signal_connect (ph->priv->host,
                          "dock",
                          (GCallback) dock_cb,
                          (gpointer) ph);

#ifdef PLACEHOLDER_DEBUG
    g_message ("Host just connected!, ph = %p", ph);
#endif
}
