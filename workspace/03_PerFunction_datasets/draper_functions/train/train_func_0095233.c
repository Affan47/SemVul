get_interface_addresses(
    const char *ifname)
{
  struct ifaddrs	*addrs,
			*addr;
  http_addrlist_t	*first,
			*last,
			*current;


  if (getifaddrs(&addrs) < 0)
    return (NULL);

  for (addr = addrs, first = NULL, last = NULL; addr; addr = addr->ifa_next)
    if ((addr->ifa_flags & IFF_BROADCAST) && addr->ifa_broadaddr &&
        addr->ifa_broadaddr->sa_family == AF_INET &&
	(!ifname || !strcmp(ifname, addr->ifa_name)))
    {
      current = calloc(1, sizeof(http_addrlist_t));

      memcpy(&(current->addr), addr->ifa_broadaddr,
             sizeof(struct sockaddr_in));

      if (!last)
        first = current;
      else
        last->next = current;

      last = current;
    }

  freeifaddrs(addrs);

  return (first);
}
