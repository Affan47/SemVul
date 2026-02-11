fetch_data(const char *host)
{
   int nis_port = NISPORT;
   int sockfd;
   int stat;
   char *p;
   char lhost[200];

   if (statlen != 0 && (strcmp(last_host, host) == 0))
       return 1;
   strncpy(last_host, host, sizeof(last_host));
   last_host[sizeof(last_host) - 1] = '\0';
   statlen = 0;
   strncpy(lhost, host, sizeof(lhost)-1);
   lhost[sizeof(lhost)-1] = '\0';
   p = strchr(lhost, ':');
   if (p) {
      *p++ = '\0';
      nis_port = atoi(p);
   }
   if ((sockfd = net_open(lhost, NULL, nis_port)) < 0) {
      (void) snprintf(errmsg, sizeof (errmsg),
         "upsfetch: tcp_open failed for %s port %d", lhost, nis_port);
      return 0;
   }

   stat = fill_buffer(sockfd);
   if (stat == 0) {
      *last_host = '\0';
      statlen = 0;
   }
   net_close(sockfd);
   return stat;
}
