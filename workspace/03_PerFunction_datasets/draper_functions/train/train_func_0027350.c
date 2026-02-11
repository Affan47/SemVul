nice_interfaces_get_local_ips (gboolean include_loopback)
{
  GList *ips = NULL;
  struct ifaddrs *ifa, *results;
  GList *loopbacks = NULL;


  if (getifaddrs (&results) < 0)
      return NULL;


  for (ifa = results; ifa; ifa = ifa->ifa_next) {
    char addr_as_string[INET6_ADDRSTRLEN+1];


    if ((ifa->ifa_flags & IFF_UP) == 0)
      continue;

    if (ifa->ifa_addr == NULL) {
      continue;
    } else if (ifa->ifa_addr->sa_family == AF_INET) {
      struct sockaddr_in *sa4 = (struct sockaddr_in *) ifa->ifa_addr;

      if (inet_ntop (AF_INET, &sa4->sin_addr, addr_as_string,
              INET6_ADDRSTRLEN) == NULL)
        continue;
    } else if (ifa->ifa_addr->sa_family == AF_INET6) {
      struct sockaddr_in6 *sa6 = (struct sockaddr_in6 *)ifa->ifa_addr;


      if (IN6_IS_ADDR_LINKLOCAL (&sa6->sin6_addr))
        continue;

      if (inet_ntop (AF_INET6, &sa6->sin6_addr, addr_as_string,
              INET6_ADDRSTRLEN) == NULL)
        continue;
    } else
      continue;


    nice_debug ("Interface:  %s", ifa->ifa_name);
    nice_debug ("IP Address: %s", addr_as_string);
    if ((ifa->ifa_flags & IFF_LOOPBACK) == IFF_LOOPBACK) {
      if (include_loopback)
        loopbacks = g_list_append (loopbacks, g_strdup (addr_as_string));
      else
        nice_debug ("Ignoring loopback interface");
    } else {
      if (nice_interfaces_is_private_ip (ifa->ifa_addr))
        ips = g_list_append (ips, g_strdup (addr_as_string));
      else
        ips = g_list_prepend (ips, g_strdup (addr_as_string));
    }
  }

  freeifaddrs (results);

  if (loopbacks)
    ips = g_list_concat (ips, loopbacks);

  return ips;
}
