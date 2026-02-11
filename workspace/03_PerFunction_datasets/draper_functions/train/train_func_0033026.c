do_ping (GdmHostChooserWidget *widget,
         gboolean              full)
{
        GSList *l;

        g_debug ("do ping full:%d", full);

        for (l = widget->priv->broadcast_addresses; l != NULL; l = l->next) {
                GdmAddress              *address;
                int                      res;

                address = l->data;

                gdm_address_debug (address);
                errno = 0;
                g_debug ("fd:%d", widget->priv->socket_fd);
                res = XdmcpFlush (widget->priv->socket_fd,
                                  &widget->priv->broadcast_buf,
                                  (XdmcpNetaddr)gdm_address_peek_sockaddr_storage (address),
                                  (int)gdm_sockaddr_len (gdm_address_peek_sockaddr_storage (address)));

                if (! res) {
                        g_warning ("Unable to flush the XDMCP broadcast packet: %s", g_strerror (errno));
                }
        }

        if (full) {
                for (l = widget->priv->query_addresses; l != NULL; l = l->next) {
                        GdmAddress *address;
                        int         res;

                        address = l->data;

                        gdm_address_debug (address);
                        res = XdmcpFlush (widget->priv->socket_fd,
                                          &widget->priv->query_buf,
                                          (XdmcpNetaddr)gdm_address_peek_sockaddr_storage (address),
                                          (int)gdm_sockaddr_len (gdm_address_peek_sockaddr_storage (address)));
                        if (! res) {
                                g_warning ("Unable to flush the XDMCP query packet");
                        }
                }
        }
}
