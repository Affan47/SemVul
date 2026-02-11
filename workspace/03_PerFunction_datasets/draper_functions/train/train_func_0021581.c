ToSockAddrStorageHelper(sockaddr_storage* addr,
                                      IPAddress ip, int port, int scope_id) {
  memset(addr, 0, sizeof(sockaddr_storage));
  addr->ss_family = ip.family();
  if (addr->ss_family == AF_INET6) {
    sockaddr_in6* saddr = reinterpret_cast<sockaddr_in6*>(addr);
    saddr->sin6_addr = ip.ipv6_address();
    saddr->sin6_port = HostToNetwork16(port);
    saddr->sin6_scope_id = scope_id;
    return sizeof(sockaddr_in6);
  } else if (addr->ss_family == AF_INET) {
    sockaddr_in* saddr = reinterpret_cast<sockaddr_in*>(addr);
    saddr->sin_addr = ip.ipv4_address();
    saddr->sin_port = HostToNetwork16(port);
    return sizeof(sockaddr_in);
  }
  return 0;
}
