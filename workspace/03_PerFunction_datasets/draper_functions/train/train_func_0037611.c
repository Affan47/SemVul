resolv_host(int family, const char *host, dlist * addr_list)
{
   struct hostent *hp;
   const char *errmsg;

   P(ip_mutex);
#ifdef HAVE_GETHOSTBYNAME2
   if ((hp = gethostbyname2(host, family)) == NULL) {
#else
   if ((hp = gethostbyname(host)) == NULL) {
#endif

      errmsg = gethost_strerror();
      V(ip_mutex);
      return errmsg;
   } else {
      char **p;
      for (p = hp->h_addr_list; *p != 0; p++) {
         IPADDR *addr =  New(IPADDR(hp->h_addrtype));
         addr->set_type(IPADDR::R_MULTIPLE);
         if (addr->get_family() == AF_INET) {
             addr->set_addr4((struct in_addr*)*p);
         }
#ifdef HAVE_IPV6
         else {
             addr->set_addr6((struct in6_addr*)*p);
         }
#endif
         addr_list->append(addr);
      }
      V(ip_mutex);
   }
   return NULL;
}
