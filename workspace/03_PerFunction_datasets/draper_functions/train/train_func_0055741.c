ooOnReceivedUserInputIndication
   (OOH323CallData *call, H245UserInputIndication *indication)
{
   if((indication->t == T_H245UserInputIndication_alphanumeric) &&
      (call->dtmfmode & OO_CAP_DTMF_H245_alphanumeric))
   {
      if(gH323ep.h323Callbacks.onReceivedDTMF)
         gH323ep.h323Callbacks.onReceivedDTMF(call,indication->u.alphanumeric);
   }
   else if((indication->t == T_H245UserInputIndication_signal) &&
           (call->dtmfmode & OO_CAP_DTMF_H245_signal)) {
      if(call->lastDTMF && indication->u.signal->signalType[0] == call->lastDTMF &&
         call->nextDTMFstamp && indication->u.signal->m.rtpPresent &&
         indication->u.signal->rtp.m.timestampPresent) {
	  if(call->nextDTMFstamp > indication->u.signal->rtp.timestamp) {
            OOTRACEERR4("ERROR:Duplicate dtmf %c on ((%s, %s)\n", call->lastDTMF, call->callType,
			call->callToken);
	    return OO_OK;
          }
      }
      if (indication->u.signal->m.rtpPresent && indication->u.signal->rtp.m.timestampPresent &&
          indication->u.signal->m.durationPresent) {
          call->nextDTMFstamp = indication->u.signal->rtp.timestamp +
				indication->u.signal->duration;
	  call->lastDTMF = indication->u.signal->signalType[0];
      } else {
	  call->nextDTMFstamp = 0;
	  call->lastDTMF = 0;
      }
      if(gH323ep.h323Callbacks.onReceivedDTMF)
         gH323ep.h323Callbacks.onReceivedDTMF(call,
                                             indication->u.signal->signalType);
   }
   else {
      OOTRACEINFO3("Unsupported userInput message type received - ignoring."
                   "(%s, %s)\n", call->callType, call->callToken);
   }
   return OO_OK;
}
