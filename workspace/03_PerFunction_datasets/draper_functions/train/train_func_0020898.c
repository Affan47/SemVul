create_mcast_client(apr_pool_t *context, char *mcast_ip, apr_port_t port, int ttl, const char *interface, char *bind_address, int bind_hostname)
{
    apr_socket_t *socket = create_udp_client(context, mcast_ip, port, interface, bind_address, bind_hostname);
    if(!socket)
      {
        return NULL;
      }
    apr_mcast_hops(socket, ttl);

    mcast_emit_on_if( context, socket, mcast_ip, port, interface);

    return socket;
}
