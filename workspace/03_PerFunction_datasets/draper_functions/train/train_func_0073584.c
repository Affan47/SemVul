SendAvrsUpdate(AVRS_State State,char *Callsign)
{
   char TempSDES[512];
   int   Len = 0;
   IPAdrUnion HisAdr;
   struct hostent *pHost;
   int Sent;

   if(AvrsEnable && LoginInterval > 0) {
      Len = CreateAvrsPacket(State,Callsign,TempSDES,sizeof(TempSDES));
   }

   if(Len > 0) {
      pHost = GetHostByName("aprs.echolink.org");
      if(pHost != NULL) {
         HisAdr.i.sin_addr.s_addr = IP_FROM_HOSTENT(pHost,0);
         HisAdr.i.sin_family = AF_INET;
         HisAdr.PORT = htons(ILINK_RTCP_PORT);
         Sent = sendto(piLinkConf->pControl->Socket,TempSDES,Len,0,&HisAdr.s,
                       sizeof(HisAdr));
         if(Sent != Len) {
            LOG_ERROR(("SendAvrsUpdate: sendto failed, %s",Err2String(errno)));
         }
      }
   }
}
