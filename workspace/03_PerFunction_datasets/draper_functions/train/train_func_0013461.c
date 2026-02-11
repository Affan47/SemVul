ooGkClientInit(enum RasGatekeeperMode eGkMode,
              char *szGkAddr, int iGkPort )
{
   ooGkClient *pGkClient=NULL;
   OOInterface *cur=NULL;
   pGkClient = (ooGkClient*)
                         memAlloc(&gH323ep.ctxt, sizeof(ooGkClient));
   if(!pGkClient)
   {
      OOTRACEERR1("Error: Failed to allocate memory to Gatekeeper Client.\n");
      return OO_FAILED;
   }

   memset(pGkClient, 0, sizeof(ooGkClient));
   ast_mutex_init(&pGkClient->Lock);
   gH323ep.gkClient = pGkClient;
   initContext(&(pGkClient->ctxt));
   initContext(&(pGkClient->msgCtxt));
   pGkClient->rrqRetries = 0;
   pGkClient->grqRetries = 0;

   strcpy(pGkClient->localRASIP, gH323ep.signallingIP);
#ifndef _WIN32
   if(!strcmp(pGkClient->localRASIP, "0.0.0.0") ||
      !strcmp(pGkClient->localRASIP, "127.0.0.1"))
   {
      if(!gH323ep.ifList)
      {
         if(ooSocketGetInterfaceList(&gH323ep.ctxt, &gH323ep.ifList)!= ASN_OK)
         {
            OOTRACEERR1("Error:Failed to retrieve interface addresses\n");
            return OO_FAILED;
         }
      }
      for(cur = gH323ep.ifList; cur; cur = cur->next)
      {
         if(!strcmp(cur->name, "lo") || !strcmp(cur->addr, "127.0.0.1"))
            continue;
         break;
      }
      if(cur)
      {
         OOTRACEINFO2("Using local RAS Ip address %s\n", cur->addr);
         strcpy(pGkClient->localRASIP, cur->addr);
      }
      else{
         OOTRACEERR1("Error:Failed to assign a local RAS IP address\n");
         return OO_FAILED;
      }
   }
#endif
   if(OO_OK != ooGkClientSetGkMode(pGkClient, eGkMode, szGkAddr, iGkPort))
   {
      OOTRACEERR1("Error:Failed to set Gk mode\n");
      memReset(&gH323ep.ctxt);
      return OO_FAILED;
   }


   pGkClient->grqTimeout = DEFAULT_GRQ_TIMEOUT;
   pGkClient->rrqTimeout = DEFAULT_RRQ_TIMEOUT;
   pGkClient->regTimeout = DEFAULT_REG_TTL;
   pGkClient->arqTimeout = DEFAULT_ARQ_TIMEOUT;
   pGkClient->drqTimeout = DEFAULT_DRQ_TIMEOUT;
   dListInit(&pGkClient->callsPendingList);
   dListInit(&pGkClient->callsAdmittedList);
   dListInit(&pGkClient->timerList);
   pGkClient->state = GkClientIdle;
   return OO_OK;
}
