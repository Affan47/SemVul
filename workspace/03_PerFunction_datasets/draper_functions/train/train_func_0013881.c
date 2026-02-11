set_addr4(struct in_addr *ip4)
{
   if (saddr->sa_family != AF_INET) {
      Emsg1(M_ERROR_TERM, 0, _("It was tried to assign a ipv6 address to a ipv4(%d)\n"), saddr->sa_family);
   }
   saddr4->sin_addr = *ip4;
}
