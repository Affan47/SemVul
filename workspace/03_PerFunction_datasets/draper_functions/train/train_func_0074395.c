g_inetaddr_is_multicast (const g_inet_addr* inetaddr)
{
  unsigned int addr;

  if( inetaddr == NULL )
     return 0;

  addr = G_SOCKADDR_IN(inetaddr->sa).sin_addr.s_addr;
  addr = htonl(addr);

  if ((addr & 0xF0000000) == 0xE0000000)
    return 1;

  return 0;
}
