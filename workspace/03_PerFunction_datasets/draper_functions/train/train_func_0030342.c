ooCapabilityAddGSMCapability(OOH323CallData *call, int cap,
                                unsigned framesPerPkt, OOBOOL comfortNoise,
                                OOBOOL scrambled, int dir,
                                cb_StartReceiveChannel startReceiveChannel,
                                cb_StartTransmitChannel startTransmitChannel,
                                cb_StopReceiveChannel stopReceiveChannel,
                                cb_StopTransmitChannel stopTransmitChannel,
                                OOBOOL remote)
{

   ooH323EpCapability *epCap = NULL, *cur=NULL;
   OOGSMCapParams *params=NULL;
   OOCTXT *pctxt = NULL;

   if(!call) pctxt = &gH323ep.ctxt;
   else pctxt = call->pctxt;

   epCap = (ooH323EpCapability*)memAlloc(pctxt, sizeof(ooH323EpCapability));
   params = (OOGSMCapParams*) memAlloc(pctxt, sizeof(OOGSMCapParams));
   if(!epCap || !params)
   {
      OOTRACEERR1("Error:Memory - ooCapabilityAddGSMCapability - "
                  "epCap/params\n");
      return OO_FAILED;
   }


   params->rxframes = framesPerPkt;
   params->txframes = framesPerPkt;
   params->comfortNoise = comfortNoise;
   params->scrambled = scrambled;
   if(dir & OORXANDTX)
   {
      epCap->dir = OORX;
      epCap->dir |= OOTX;
   }
   else
      epCap->dir = dir;

   epCap->cap = cap;
   epCap->capType = OO_CAP_TYPE_AUDIO;
   epCap->params = (void*)params;
   epCap->startReceiveChannel = startReceiveChannel;
   epCap->startTransmitChannel = startTransmitChannel;
   epCap->stopReceiveChannel = stopReceiveChannel;
   epCap->stopTransmitChannel = stopTransmitChannel;

   epCap->next = NULL;

   if(!call)
   {
      if(!gH323ep.myCaps)
         gH323ep.myCaps = epCap;
      else{
         cur = gH323ep.myCaps;
         while(cur->next) cur = cur->next;
         cur->next = epCap;
      }
      ooAppendCapToCapPrefs(NULL, cap);
      gH323ep.noOfCaps++;
   }
   else{
      if(remote)
      {

         if(!call->remoteCaps)
            call->remoteCaps = epCap;
         else{
            cur = call->remoteCaps;
            while(cur->next) cur = cur->next;
            cur->next = epCap;
         }
      }
      else{
         OOTRACEDBGC4("Adding call specific capability %s. (%s, %s)\n",
                     ooGetCapTypeText(epCap->cap), call->callType,
                     call->callToken);

         if(!call->ourCaps){
            call->ourCaps = epCap;
            ooResetCapPrefs(call);
         }
         else{
            cur = call->ourCaps;
            while(cur->next) cur = cur->next;
            cur->next = epCap;
         }
         ooAppendCapToCapPrefs(call, cap);
      }
   }

   return OO_OK;
}
