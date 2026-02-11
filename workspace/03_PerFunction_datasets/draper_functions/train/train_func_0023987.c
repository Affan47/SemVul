open_tcp_socket (GSocketFamily family, guint port, GError **error)
{
    GSocket *socket;
    GSocketAddress *address;

    socket = g_socket_new (family, G_SOCKET_TYPE_STREAM, G_SOCKET_PROTOCOL_TCP, error);
    if (!socket)
        return NULL;

    address = g_inet_socket_address_new (g_inet_address_new_any (family), port);
    if (!g_socket_bind (socket, address, TRUE, error) ||
        !g_socket_listen (socket, error))
    {
        g_object_unref (socket);
        return NULL;
    }

    return socket;
}
