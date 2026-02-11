smux_master_is_running()
{
   struct servent  *pse;
   struct protoent *ppe;
   struct sockaddr_in sin = {0};
   int    s;

   sin.sin_family = AF_INET;
   sin.sin_addr.s_addr = INADDR_ANY;

   if ((pse = getservbyname("smux", "tcp"))) {
      sin.sin_port = ntohs(pse->s_port);
   } else {
      sin.sin_port = 199;
   }

   if ((ppe = getprotobyname("tcp")) == 0) {
      return(0);
   }

   if ((s = socket(AF_INET, SOCK_STREAM, ppe->p_proto)) < 0) {
      return(0);
   }


   sin.sin_port = htons(sin.sin_port);
   if (bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
      close(s);
      return(1);
   } else {
   }

   close(s);
   return(0);
}
