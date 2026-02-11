sigar_net_address_to_string(sigar_t *sigar,
                                               sigar_net_address_t *address,
                                               char *addr_str)
{
    *addr_str = '\0';
    switch (address->family) {
      case SIGAR_AF_INET6:
        if (sigar_inet_ntop(AF_INET6, (const void *)&address->addr.in6,
                            addr_str, SIGAR_INET6_ADDRSTRLEN))
        {
            return SIGAR_OK;
        }
        else {
            return sigar_inet_ntop_errno;
        }
      case SIGAR_AF_INET:
        return sigar_inet_ntoa(sigar, address->addr.in, addr_str);
      case SIGAR_AF_UNSPEC:
        return sigar_inet_ntoa(sigar, 0, addr_str);
      case SIGAR_AF_LINK:
        return sigar_ether_ntoa(addr_str, &address->addr.mac[0]);
      default:
        return EINVAL;
    }
}
