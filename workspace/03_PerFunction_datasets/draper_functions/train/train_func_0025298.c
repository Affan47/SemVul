__get_socket (struct sockaddr_in *saddr)
{
  int so = __socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (so < 0)
    return -1;

  struct sockaddr_in laddr;
  socklen_t namelen = sizeof (laddr);
  laddr.sin_family = AF_INET;
  laddr.sin_port = 0;
  laddr.sin_addr.s_addr = htonl (INADDR_ANY);

  int cc = __bind (so, (struct sockaddr *) &laddr, namelen);
  if (__builtin_expect (cc < 0, 0))
    {
    fail:
      __close (so);
      return -1;
    }

  cc = __connect (so, (struct sockaddr *) saddr, namelen);
  if (__builtin_expect (cc < 0, 0))
    goto fail;

  return so;
}
