PackAddressForNAT(char* buf, size_t buf_size,
                         const SocketAddress& remote_addr) {
  const IPAddress& ip = remote_addr.ipaddr();
  int family = ip.family();
  buf[0] = 0;
  buf[1] = family;

  *(reinterpret_cast<uint16*>(&buf[2])) = HostToNetwork16(remote_addr.port());
  if (family == AF_INET) {
    ASSERT(buf_size >= kNATEncodedIPv4AddressSize);
    in_addr v4addr = ip.ipv4_address();
    std::memcpy(&buf[4], &v4addr, kNATEncodedIPv4AddressSize - 4);
    return kNATEncodedIPv4AddressSize;
  } else if (family == AF_INET6) {
    ASSERT(buf_size >= kNATEncodedIPv6AddressSize);
    in6_addr v6addr = ip.ipv6_address();
    std::memcpy(&buf[4], &v6addr, kNATEncodedIPv6AddressSize - 4);
    return kNATEncodedIPv6AddressSize;
  }
  return 0U;
}
