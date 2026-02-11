sock_any_ntop(const struct sockaddr_any* any, char* addr, size_t addrlen, int opts)
{
  int len = 0;
  int port = 0;

  switch(any->s.a.sa_family)
  {
  case AF_UNIX:
    len = strlen(any->s.un.sun_path);
    if(addrlen < len + 1)
    {
      errno = ENOSPC;
      return -1;
    }

    strcpy(addr, any->s.un.sun_path);
    break;

  case AF_INET:
    if(inet_ntop(any->s.a.sa_family, &(any->s.in.sin_addr), addr, addrlen) == NULL)
      return -1;
    port = ntohs(any->s.in.sin_port);
    break;

#ifdef HAVE_INET6
  case AF_INET6:
    if(inet_ntop(any->s.a.sa_family, &(any->s.in6.sin6_addr), addr, addrlen) == NULL)
      return -1;
    port = ntohs(any->s.in6.sin6_port);
    break;
#endif

  default:
    errno = EAFNOSUPPORT;
    return -1;
  }

  if(!(opts & SANY_OPT_NOPORT) && port != 0)
  {
    strncat(addr, ":", addrlen);
    addr[addrlen - 1] = 0;

    len = strlen(addr);
    addr += len;
    addrlen -= len;

    snprintf(addr, addrlen, "%d", port);
  }

  return 0;
}
