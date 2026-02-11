FindGlobalIPv6Address()
{
#ifdef HAVE_IFADDRS_H
   struct ifaddrs *ifaddrs=0;
   getifaddrs(&ifaddrs);
   for(struct ifaddrs *ifa=ifaddrs; ifa; ifa=ifa->ifa_next) {
      if(ifa->ifa_addr && ifa->ifa_addr->sa_family==AF_INET6) {
	 struct in6_addr *addr=&((struct sockaddr_in6*)ifa->ifa_addr)->sin6_addr;
	 if(!IN6_IS_ADDR_UNSPECIFIED(addr) && !IN6_IS_ADDR_LOOPBACK(addr)
	 && !IN6_IS_ADDR_LINKLOCAL(addr) && !IN6_IS_ADDR_SITELOCAL(addr)
	 && !IN6_IS_ADDR_MULTICAST(addr)) {
	    char *buf=xstring::tmp_buf(INET6_ADDRSTRLEN);
	    inet_ntop(AF_INET6, addr, buf, INET6_ADDRSTRLEN);
	    freeifaddrs(ifaddrs);
	    return buf;
	 }
      }
   }
   freeifaddrs(ifaddrs);
#endif
   return 0;
}
