get_ip()
{
  struct hostent *hp;
  IP ip;
  struct in_addr *in;


  if (uptime_host[0]) {
    if ((uptime_host[strlen(uptime_host) - 1] >= '0') &&
        (uptime_host[strlen(uptime_host) - 1] <= '9'))
      return (IP) inet_addr(uptime_host);
  }
  hp = gethostbyname(uptime_host);
  if (hp == NULL)
    return -1;
  in = (struct in_addr *) (hp->h_addr_list[0]);
  ip = (IP) (in->s_addr);
  return ip;
}
