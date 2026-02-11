etheraddr_string(u_char *ep)
{
   u_int i, j;
   char *cp;
   struct enamemem *tp;

   tp = lookup_emem(ep);
   if (tp->e_name)
      return (tp->e_name);
#if defined(ETHER_SERVICE) && !defined(linux) && !defined(CYGWIN)
   if (!nflag) {
      char buf[128];
      if (ether_ntohost(buf, (struct ether_addr *)ep) == 0) {
         tp->e_name = savestr(buf);
         return (tp->e_name);
      }
   }
#endif
   tp->e_name = cp = (char *)malloc(sizeof("00:00:00:00:00:00"));

   if ((j = *ep >> 4) != 0)
      *cp++ = hex[j];
   *cp++ = hex[*ep++ & 0xf];
   for (i = 5; (int)--i >= 0;) {
      *cp++ = ':';
      if ((j = *ep >> 4) != 0)
         *cp++ = hex[j];
      *cp++ = hex[*ep++ & 0xf];
   }
   *cp = '\0';
   return (tp->e_name);
}
