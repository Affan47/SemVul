sockaddr_ntop(struct sockaddr *sa)

{
#if defined(HAVE_GETADDRINFO)
 static char addrbuf[INET6_ADDRSTRLEN];
 void *addr;
#else
 static char addrbuf[20];
 struct in_addr addr;
#endif

switch (sa->sa_family)
   {
   case AF_INET:
       Debug("IPV4 address\n");
       snprintf(addrbuf,20,"%.19s",inet_ntoa(((struct sockaddr_in *)sa)->sin_addr));
       break;

#ifdef AF_LOCAL
   case AF_LOCAL:
       Debug("Local socket\n") ;
       strcpy(addrbuf, "127.0.0.1") ;
       break;
#endif

#if defined(HAVE_GETADDRINFO)
   case AF_INET6:
       Debug("IPV6 address\n");
       addr = &((struct sockaddr_in6 *)sa)->sin6_addr;
       inet_ntop(sa->sa_family,addr,addrbuf,sizeof(addrbuf));
       break;
#endif
   default:
       Debug("Address family was %d\n",sa->sa_family);
       FatalError("Software failure in sockaddr_ntop\n");
   }

Debug("sockaddr_ntop(%s)\n",addrbuf);
return addrbuf;
}
