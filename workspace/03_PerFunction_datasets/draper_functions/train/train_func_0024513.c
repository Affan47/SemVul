prepare_socket(const char *if_name, const bjnp_sockaddr_t *local_sa,
               const bjnp_sockaddr_t *broadcast_sa, bjnp_sockaddr_t * dest_sa)
{


  int socket = -1;
  bjnp_sockaddr_t local_sa_copy;

  if ( local_sa == NULL )
    {
      PDBG (pixma_dbg (LOG_DEBUG,
                       "%s is not a valid IPv4 interface, skipping...\n",
                       if_name));
      return -1;
    }

  memset( &local_sa_copy, 0, sizeof(local_sa_copy) );
  memcpy( &local_sa_copy, local_sa, sa_size(local_sa) );

  switch( local_sa_copy.sa.sa_family )
    {
      case AF_INET:
        {
          local_sa_copy.ipv4.sin_port = htons(BJNP_PORT_SCAN);

          if (local_sa_copy.ipv4.sin_addr.s_addr == htonl (INADDR_LOOPBACK) )
            {


              PDBG (pixma_dbg (LOG_DEBUG,
                               "%s is not a valid IPv4 interface, skipping...\n",
	                       if_name));
              return -1;
            }


          memcpy(dest_sa, broadcast_sa, sa_size(dest_sa) );
          dest_sa -> ipv4.sin_port = htons(BJNP_PORT_SCAN);
          if ( (socket = create_broadcast_socket( &local_sa_copy) ) != -1)
            {
               PDBG (pixma_dbg (LOG_INFO, "%s is IPv4 capable, sending broadcast, socket = %d\n",
                      if_name, socket));
            }
          else
            {
              PDBG (pixma_dbg (LOG_INFO, "%s is IPv4 capable, but failed to create a socket.\n",
                    if_name));
              return -1;
            }
        }
        break;
#ifdef ENABLE_IPV6
      case AF_INET6:
        {
          local_sa_copy.ipv6.sin6_port = htons(BJNP_PORT_SCAN);

          if (IN6_IS_ADDR_LOOPBACK( local_sa_copy.ipv6.sin6_addr.s6_addr )  )
            {


              PDBG (pixma_dbg (LOG_DEBUG,
                               "%s is not a valid IPv6 interface, skipping...\n",
	                       if_name));
              return -1;
            }
          else
            {
              dest_sa -> ipv6.sin6_family = AF_INET6;
              dest_sa -> ipv6.sin6_port = htons(BJNP_PORT_SCAN);
              inet_pton(AF_INET6, "ff02::1", dest_sa -> ipv6.sin6_addr.s6_addr);
              if ( (socket = create_broadcast_socket( &local_sa_copy ) ) != -1)
                {
                   PDBG (pixma_dbg (LOG_INFO, "%s is IPv6 capable, sending broadcast, socket = %d\n",
                          if_name, socket));
                }
              else
                {
                  PDBG (pixma_dbg (LOG_INFO, "%s is IPv6 capable, but failed to create a socket.\n",
                        if_name));
                  return -1;
                }
            }
          }
          break;
#endif

      default:
        socket = -1;
    }
  return socket;
}
