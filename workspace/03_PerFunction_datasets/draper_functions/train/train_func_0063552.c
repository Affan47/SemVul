get_proxy_addrport(tor_addr_t *addr, uint16_t *port, int *proxy_type,
                   const connection_t *conn)
{
  const or_options_t *options = get_options();

  if (options->HTTPSProxy) {
    tor_addr_copy(addr, &options->HTTPSProxyAddr);
    *port = options->HTTPSProxyPort;
    *proxy_type = PROXY_CONNECT;
    return 0;
  } else if (options->Socks4Proxy) {
    tor_addr_copy(addr, &options->Socks4ProxyAddr);
    *port = options->Socks4ProxyPort;
    *proxy_type = PROXY_SOCKS4;
    return 0;
  } else if (options->Socks5Proxy) {
    tor_addr_copy(addr, &options->Socks5ProxyAddr);
    *port = options->Socks5ProxyPort;
    *proxy_type = PROXY_SOCKS5;
    return 0;
  } else if (options->ClientTransportPlugin ||
             options->Bridges) {
    const transport_t *transport = NULL;
    int r;
    r = find_transport_by_bridge_addrport(&conn->addr, conn->port, &transport);
    if (r<0)
      return -1;
    if (transport) {
      tor_addr_copy(addr, &transport->addr);
      *port = transport->port;
      *proxy_type = transport->socks_version;
      return 0;
    }
  }

  *proxy_type = PROXY_NONE;
  return 0;
}
