ooFindLogicalChannel(OOH323CallData *call, int sessionID,
                                        char *dir, H245DataType * dataType)
{
   OOLogicalChannel * pChannel = NULL;
   pChannel = call->logicalChans;
   while(pChannel)
   {
      OOTRACEDBGC3("ooFindLogicalChannel, checking channel: %d:%s\n",
                    pChannel->sessionID, pChannel->dir);
      if(pChannel->sessionID == sessionID || pChannel->sessionID == 0)
      {
         if(!strcmp(pChannel->dir, dir))
         {
            OOTRACEDBGC3("ooFindLogicalChannel, comparing channel: %d:%s\n",
                          pChannel->channelNo, pChannel->dir);
            if(!strcmp(dir, "receive"))
            {
               if(ooCapabilityCheckCompatibility(call, pChannel->chanCap,
                                                 dataType, OORX)) {
                  return pChannel;
               }
            }
            else if(!strcmp(dir, "transmit"))
            {
               if(ooCapabilityCheckCompatibility(call, pChannel->chanCap,
                                                 dataType, OOTX)) {
                  return pChannel;
               }
            }
         }
      }
      pChannel = pChannel->next;
   }
   return NULL;
}
