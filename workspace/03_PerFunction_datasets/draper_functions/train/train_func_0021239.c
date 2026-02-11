sprintaddr(char* buf, size_t size, struct addrinfo *a)
{
   char host[NI_MAXHOST], serv[NI_MAXSERV];
   int res;

   res = getnameinfo(a->ai_addr, a->ai_addrlen,
               host, sizeof(host),
               serv, sizeof(serv),
               numeric ? NI_NUMERICHOST | NI_NUMERICSERV : 0 );

   if (res) {
       log_message(LOG_ERR, "sprintaddr:getnameinfo: %s\n", gai_strerror(res));

       res = getnameinfo(a->ai_addr, a->ai_addrlen,
                         host, sizeof(host),
                         serv, sizeof(serv),
                         NI_NUMERICHOST | NI_NUMERICSERV);

       if (res) {
           log_message(LOG_ERR, "sprintaddr:getnameinfo(NUM): %s\n", gai_strerror(res));
           strcpy(host, "?");
           strcpy(serv, "?");
       }
   }

   snprintf(buf, size, "%s:%s", host, serv);

   return buf;
}
