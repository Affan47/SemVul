httpAddrConnect(
    http_addrlist_t *addrlist,
    int             *sock)
{
  int	val;


  while (addrlist)
  {


    if ((*sock = socket(addrlist->addr.addr.sa_family, SOCK_STREAM, 0)) < 0)
    {


      addrlist = addrlist->next;
      continue;
    }


    val = 1;
#ifdef WIN32
    setsockopt(*sock, SOL_SOCKET, SO_REUSEADDR, (const char *)&val,
               sizeof(val));
#else
    setsockopt(*sock, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
#endif

#ifdef SO_REUSEPORT
    val = 1;
    setsockopt(*sock, SOL_SOCKET, SO_REUSEPORT, &val, sizeof(val));
#endif

#ifdef SO_NOSIGPIPE
    val = 1;
    setsockopt(*sock, SOL_SOCKET, SO_NOSIGPIPE, &val, sizeof(val));
#endif


    val = 1;
#ifdef WIN32
    setsockopt(*sock, IPPROTO_TCP, TCP_NODELAY, (const char *)&val,
               sizeof(val));
#else
    setsockopt(*sock, IPPROTO_TCP, TCP_NODELAY, &val, sizeof(val));
#endif

#ifdef FD_CLOEXEC


    fcntl(*sock, F_SETFD, FD_CLOEXEC);
#endif


    if (!connect(*sock, &(addrlist->addr.addr),
                 httpAddrLength(&(addrlist->addr))))
      break;


#ifdef WIN32
    closesocket(*sock);
#else
    close(*sock);
#endif

    addrlist = addrlist->next;
  }

  return (addrlist);
}
