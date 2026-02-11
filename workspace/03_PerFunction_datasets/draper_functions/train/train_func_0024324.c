ooGkClientHandleUnregistrationRequest
   (ooGkClient *pGkClient, H225UnregistrationRequest * punregistrationRequest)
{
   int iRet=0, x;
   OOTimer *pTimer = NULL;
   DListNode *pNode = NULL;


   ooGkClientSendUnregistrationConfirm(pGkClient,
                                      punregistrationRequest->requestSeqNum);

   if(punregistrationRequest->m.endpointAliasPresent)
   {
      OOTRACEINFO1("Gatekeeper requested a list of aliases be unregistered\n");
      ooGkClientUpdateRegisteredAliases(pGkClient,
                                &punregistrationRequest->endpointAlias, FALSE);
   }
   else{

      OOTRACEINFO1("Gatekeeper requested a all aliases to be unregistered\n");
      ooGkClientUpdateRegisteredAliases(pGkClient, NULL, FALSE);


      OOTRACEINFO1("Sending fresh RRQ - as unregistration request received\n");
      pGkClient->rrqRetries = 0;
      pGkClient->state = GkClientDiscovered;


	pNode = NULL;
	for(x=0; x<pGkClient->timerList.count; x++) {
		pNode =  dListFindByIndex(&pGkClient->timerList, x);
		pTimer = (OOTimer*)pNode->data;
		if(((ooGkClientTimerCb*)pTimer->cbData)->timerType & OO_RRQ_TIMER) {
         		memFreePtr(&pGkClient->ctxt, pTimer->cbData);
         		ooTimerDelete(&pGkClient->ctxt, &pGkClient->timerList, pTimer);
         		OOTRACEDBGA1("Deleted RRQ Timer.\n");
      		}
		if(((ooGkClientTimerCb*)pTimer->cbData)->timerType & OO_REG_TIMER) {
         		memFreePtr(&pGkClient->ctxt, pTimer->cbData);
         		ooTimerDelete(&pGkClient->ctxt, &pGkClient->timerList, pTimer);
         		OOTRACEDBGA1("Deleted REG Timer.\n");
      		}
 	}

      iRet = ooGkClientSendRRQ(pGkClient, 0);
      if(iRet != OO_OK)
      {
         OOTRACEERR1("Error: Failed to send RRQ message\n");
         return OO_FAILED;
      }
   }


   if(pGkClient->callbacks.onReceivedUnregistrationRequest)
      pGkClient->callbacks.onReceivedUnregistrationRequest(
                                      punregistrationRequest, gH323ep.aliases);
   return OO_OK;
}
