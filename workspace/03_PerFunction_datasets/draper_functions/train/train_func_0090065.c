gdm_xdmcp_really_send_managed_forward (GdmXdmcpDisplayFactory *factory,
                                       GdmAddress      *address,
                                       GdmAddress      *origin)
{
        ARRAY8      addr;
        XdmcpHeader header;
        char       *host;

        host = NULL;
        gdm_address_get_numeric_info (address, &host, NULL);
        g_debug ("GdmXdmcpDisplayFactory: Sending MANAGED_FORWARD to %s",
                host ? host : "(null)");
        g_free (host);

        set_address_for_request (origin, &addr);

        header.opcode = (CARD16) GDM_XDMCP_MANAGED_FORWARD;
        header.length = 4 + addr.length;
        header.version = GDM_XDMCP_PROTOCOL_VERSION;
        XdmcpWriteHeader (&factory->priv->buf, &header);

        XdmcpWriteARRAY8 (&factory->priv->buf, &addr);
        XdmcpFlush (factory->priv->socket_fd,
                    &factory->priv->buf,
                    (XdmcpNetaddr)gdm_address_peek_sockaddr_storage (address),
                    (int)gdm_sockaddr_len (gdm_address_peek_sockaddr_storage (address)));

        g_free (addr.data);
}
