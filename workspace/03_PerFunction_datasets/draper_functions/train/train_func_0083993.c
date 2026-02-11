gethostbyname_thsafe (char *host)
{
  int res;
  unsigned int dst;
  struct addrinfo hint, *addr;

  memset(&hint, 0, sizeof(hint));
  hint.ai_family = PF_INET;
  res = getaddrinfo(host, NULL, &hint, &addr);


  if (res)
	return 0xffffffff;

  dst = ((struct sockaddr_in *)(addr->ai_addr))->sin_addr.s_addr;
  freeaddrinfo(addr);

  return dst;
}
