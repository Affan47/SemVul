Handle_EPSV()
{
   char delim;
   char *format=alloca_strdup("|||%u|");
   unsigned port;

   const char *c=strchr(line,'(');
   c=c?c+1:line+4;
   delim=*c;

   for(char *p=format; *p; p++)
      if(*p=='|')
	 *p=delim;

   if(sscanf(c,format,&port)!=1)
   {
      LogError(0,_("cannot parse EPSV response"));
      Disconnect();
      return PASV_NO_ADDRESS_YET;
   }

   socklen_t len=sizeof(conn->data_sa);
   getpeername(conn->control_sock,&conn->data_sa.sa,&len);
   if(conn->data_sa.sa.sa_family==AF_INET)
      conn->data_sa.in.sin_port=htons(port);
#if INET6
   else if(conn->data_sa.sa.sa_family==AF_INET6)
      conn->data_sa.in6.sin6_port=htons(port);
#endif
   else
   {
      Disconnect();
      return PASV_NO_ADDRESS_YET;
   }
   return PASV_HAVE_ADDRESS;
}
