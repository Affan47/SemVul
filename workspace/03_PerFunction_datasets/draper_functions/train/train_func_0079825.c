ooHandleTunneledH245Messages
   (OOH323CallData *call, H225H323_UU_PDU * pH323UUPdu)
{
   H245Message *pmsg;
   OOCTXT *pctxt = call->msgctxt;
   int ret=0,i=0;

   OOTRACEDBGC3("Checking for tunneled H.245 messages (%s, %s)\n",
                 call->callType, call->callToken);


   if(pH323UUPdu->m.h245TunnelingPresent)
   {
      if(pH323UUPdu->h245Tunneling)
      {
         OOTRACEDBGB4("Total number of tunneled H245 messages are %d.(%s, %s)"
                      "\n", (int)pH323UUPdu->h245Control.n, call->callType,
                      call->callToken);
         for(i=0; i< (int)pH323UUPdu->h245Control.n; i++)
         {
            OOTRACEDBGC5("Retrieving %d of %d tunneled H.245 messages."
                         "(%s, %s)\n",i+1, pH323UUPdu->h245Control.n,
                         call->callType, call->callToken);
            pmsg = (H245Message*)memAlloc(pctxt, sizeof(H245Message));
            if(!pmsg)
            {
               OOTRACEERR3("Error:Memory - ooHandleH245TunneledMessages - pmsg"
                          "(%s, %s)\n", call->callType, call->callToken);
               return OO_FAILED;
            }

            setPERBuffer(pctxt,
                         (ASN1OCTET*)pH323UUPdu->h245Control.elem[i].data,
                         pH323UUPdu->h245Control.elem[i].numocts, 1);

            initializePrintHandler(&printHandler, "Tunneled H.245 Message");
            memset(pmsg, 0, sizeof(H245Message));

            setEventHandler (pctxt, &printHandler);
            OOTRACEDBGC4("Decoding %d tunneled H245 message. (%s, %s)\n",
                          i+1, call->callType, call->callToken);
            ret = asn1PD_H245MultimediaSystemControlMessage(pctxt,
                                                            &(pmsg->h245Msg));
            if(ret != ASN_OK)
            {
               OOTRACEERR3("Error decoding H245 message (%s, %s)\n",
                            call->callType, call->callToken);
               ooFreeH245Message(call,pmsg);
               return OO_FAILED;
            }
            finishPrint();
            removeEventHandler (pctxt);
            ooHandleH245Message(call, pmsg);
            memFreePtr(pctxt, pmsg);
            pmsg = NULL;
         }
      }
   }
   return OO_OK;
}
