MonNetworkSnifferOpen(void)
{
char tcpbuffer[CF_BUFSIZE];

if (TCPDUMP)
   {
   struct stat statbuf;
   char buffer[CF_MAXVARSIZE];
   sscanf(CF_TCPDUMP_COMM,"%s",buffer);

   if (cfstat(buffer,&statbuf) != -1)
      {
      if ((TCPPIPE = cf_popen(CF_TCPDUMP_COMM,"r")) == NULL)
         {
         TCPDUMP = false;
         }


      fgets(tcpbuffer,CF_BUFSIZE-1,TCPPIPE);
      }
   else
      {
      TCPDUMP = false;
      }
   }
}
