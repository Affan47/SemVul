gupnp_linux_context_manager_dispose (GObject *object)
{
        GUPnPLinuxContextManager *self;
        GObjectClass *parent_class;

        self = GUPNP_LINUX_CONTEXT_MANAGER (object);

        if (self->priv->bootstrap_source != NULL) {
                g_source_destroy (self->priv->bootstrap_source);
                g_source_unref (self->priv->bootstrap_source);
                self->priv->bootstrap_source = NULL;
        }

        if (self->priv->netlink_socket_source != NULL) {
               g_source_destroy (self->priv->netlink_socket_source);
               g_source_unref (self->priv->netlink_socket_source);
               self->priv->netlink_socket_source = NULL;
        }

        if (self->priv->netlink_socket != NULL) {
                g_object_unref (self->priv->netlink_socket);
                self->priv->netlink_socket = NULL;
        }

        if (self->priv->fd != 0) {
                close (self->priv->fd);
                self->priv->fd = 0;
        }

        if (self->priv->interfaces) {
                g_hash_table_destroy (self->priv->interfaces);
                self->priv->interfaces = NULL;
        }


        parent_class = G_OBJECT_CLASS (gupnp_linux_context_manager_parent_class);
        parent_class->dispose (object);
}
