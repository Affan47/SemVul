create_broadcast_socket( const bjnp_sockaddr_t * local_addr )
{
  int sockfd = -1;
  int broadcast = 1;
  int ipv6_v6only = 1;


 if ((sockfd = socket (local_addr-> sa.sa_family, SOCK_DGRAM, 0)) == -1)
    {
      PDBG (pixma_dbg
            (LOG_CRIT, "create_broadcast_socket: can not open socket - %s",
             strerror (errno)));
      return -1;
    }


  if (setsockopt
      (sockfd, SOL_SOCKET, SO_BROADCAST, (const char *) &broadcast,
       sizeof (broadcast)) != 0)
    {
      PDBG (pixma_dbg
            (LOG_CRIT,
             "create_broadcast_socket: setting socket option SO_BROADCAST failed - %s",
             strerror (errno)));
      close (sockfd);
      return -1;
    };


  if ( (local_addr -> sa.sa_family == AF_INET6) && ( setsockopt
      (sockfd, IPPROTO_IPV6, IPV6_V6ONLY, (const char *) &ipv6_v6only,
       sizeof (ipv6_v6only)) != 0) )
    {
      PDBG (pixma_dbg
            (LOG_CRIT,
             "create_broadcast_socket: setting socket option IPV6_V6ONLY failed - %s",
             strerror (errno)));
      close (sockfd);
      return -1;
    };

  if (bind
      (sockfd, &(local_addr->in),
       (socklen_t) sa_size( local_addr)) != 0)
    {
      PDBG (pixma_dbg
            (LOG_CRIT,
             "create_broadcast_socket: bind socket to local address failed - %s\n",
             strerror (errno)));
      close (sockfd);
      return -1;
    }
  return sockfd;
}
