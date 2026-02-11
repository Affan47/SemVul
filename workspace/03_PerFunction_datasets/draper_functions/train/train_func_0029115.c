CallLog(ConfClient *pCC)
{
   static char IPAddress[1024];
   char *Ret = pCC->Callsign;

   if(LogIPAddresses) {
      snprintf(IPAddress,sizeof(IPAddress),"%s (%s)",pCC->Callsign,
               inet_ntoa(pCC->HisAdr.i.sin_addr));
      Ret = IPAddress;
   }

   return Ret;
}
