read_cb (GSocket *socket, GIOCondition condition, XDMCPServer *server)
{
    GSocketAddress *address;
    gchar data[1024];
    GError *error = NULL;
    gssize n_read;

    n_read = g_socket_receive_from (socket, &address, data, 1024, NULL, &error);
    if (error)
        g_warning ("Failed to read from XDMCP socket: %s", error->message);
    g_clear_error (&error);

    if (n_read > 0)
    {
        XDMCPPacket *packet;

        packet = xdmcp_packet_decode ((guint8 *)data, n_read);
        if (packet)
        {
            g_debug ("Got %s", xdmcp_packet_tostring (packet));

            switch (packet->opcode)
            {
            case XDMCP_BroadcastQuery:
            case XDMCP_Query:
            case XDMCP_IndirectQuery:
                handle_query (server, socket, address, packet);
                break;
            case XDMCP_Request:
                handle_request (server, socket, address, packet);
                break;
            case XDMCP_Manage:
                handle_manage (server, socket, address, packet);
                break;
            case XDMCP_KeepAlive:
                handle_keep_alive (server, socket, address, packet);
                break;
            default:
                g_warning ("Got unexpected XDMCP packet %d", packet->opcode);
                break;
            }

            xdmcp_packet_free (packet);
        }
    }

    return TRUE;
}
