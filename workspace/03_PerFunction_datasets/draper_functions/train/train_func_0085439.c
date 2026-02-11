initialise_io(int family)
{
  if (family == IPADDR_INET4 || family == IPADDR_UNSPEC)
    sock_fd4 = prepare_socket(AF_INET);
#ifdef HAVE_IPV6
  if (family == IPADDR_INET6 || family == IPADDR_UNSPEC)
    sock_fd6 = prepare_socket(AF_INET6);
#endif
}
