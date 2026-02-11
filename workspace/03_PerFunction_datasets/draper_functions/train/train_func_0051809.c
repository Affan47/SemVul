nice_address_set_ipv4 (NiceAddress *addr, guint32 addr_ipv4)
{
  addr->s.ip4.sin_family = AF_INET;
#ifdef HAVE_SA_LEN
  addr->s.ip4.sin_len = sizeof (addr->sa.ip4);
#endif
  addr->s.ip4.sin_addr.s_addr = addr_ipv4 ? htonl (addr_ipv4) : INADDR_ANY;
  addr->s.ip4.sin_port = 0;
}
