get_port_net_order() const
{
   unsigned short port = 0;
   if (saddr->sa_family == AF_INET) {
      port = saddr4->sin_port;
   }
#ifdef HAVE_IPV6
   else {
      port = saddr6->sin6_port;
   }
#endif
    return port;
}
