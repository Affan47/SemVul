ooGkClientCreateChannel(ooGkClient *pGkClient)
{
   int ret=0;
   OOIPADDR ipaddrs;

   if((ret=ooSocketCreateUDP(&pGkClient->rasSocket, 4))!=ASN_OK)
   {
      OOTRACEERR1("Failed to create RAS socket\n");
      pGkClient->state = GkClientFailed;
      return OO_FAILED;
   }
   if(pGkClient->localRASPort)
   {
      inet_pton(AF_INET, pGkClient->localRASIP, &ipaddrs);
      if( (ret=ooSocketBind( pGkClient->rasSocket, ipaddrs,
           pGkClient->localRASPort))!=ASN_OK )
      {
         OOTRACEERR1("ERROR:Failed to create RAS channel\n");
         pGkClient->state = GkClientFailed;
         return OO_FAILED;
      }
   }
   else {
      ret = ooBindPort (OOUDP, pGkClient->rasSocket, pGkClient->localRASIP);
      if(ret == OO_FAILED)
      {
         OOTRACEERR1("ERROR: Failed to bind port to RAS socket\n");
         pGkClient->state = GkClientFailed;
         return OO_FAILED;
      }
      pGkClient->localRASPort = ret;
   }


   if(!strcmp(pGkClient->localRASIP, "0.0.0.0"))
   {
      OOTRACEDBGA1("Determining ip address for RAS channel "
                   "multihomed mode. \n");
      ret = ooSocketGetIpAndPort(pGkClient->rasSocket, pGkClient->localRASIP,
                                 20, &pGkClient->localRASPort, NULL);
      if(ret != ASN_OK)
      {
         OOTRACEERR1("Error:Failed to retrieve local ip and port from "
                     "socket for RAS channel(multihomed).\n");
         pGkClient->state = GkClientFailed;
         return OO_FAILED;
      }
      OOTRACEDBGA3("Using local ip %s and port %d for RAS channel"
                   "(multihomedMode).\n", pGkClient->localRASIP,
                   pGkClient->localRASPort);
   }

   OOTRACEINFO1("H323 RAS channel creation - successful\n");
   return OO_OK;
}
