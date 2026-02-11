on_bootstrap (GUPnPLinuxContextManager *self)
{
        if (self->priv->nl_seq == 0) {
                query_all_network_interfaces (self);

                return TRUE;
        } else if (self->priv->nl_seq == 1) {
                query_all_addresses (self);

                return TRUE;
        } else {
                self->priv->netlink_socket_source = g_socket_create_source
                                                (self->priv->netlink_socket,
                                                 G_IO_IN | G_IO_PRI,
                                                 NULL);

                g_source_attach (self->priv->netlink_socket_source,
                                 g_main_context_get_thread_default ());

                g_source_set_callback (self->priv->netlink_socket_source,
                                       (GSourceFunc)
                                       on_netlink_message_available,
                                       self,
                                       NULL);
        }

        return FALSE;
}
