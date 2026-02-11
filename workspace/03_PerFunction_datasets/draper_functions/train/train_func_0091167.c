is_reserved() const
{
   if(sa.sa_family==AF_INET)
   {
      unsigned char *a=(unsigned char *)&in.sin_addr;
      return (a[0]==0)
	  || (a[0]==127 && !is_loopback())
	  || (a[0]>=240);
   }
#if INET6
   if(family()==AF_INET6) {
      return IN6_IS_ADDR_UNSPECIFIED(&in6.sin6_addr)
	  || IN6_IS_ADDR_V4MAPPED(&in6.sin6_addr)
	  || IN6_IS_ADDR_V4COMPAT(&in6.sin6_addr);
   }
#endif
   return false;
}
