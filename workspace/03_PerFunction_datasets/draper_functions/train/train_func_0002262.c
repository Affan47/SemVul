ooSendRequestChannelCloseRelease(OOH323CallData *call, int channelNum)
{
   int ret = OO_OK;
   H245Message *ph245msg = NULL;
   OOCTXT *pctxt;
   H245IndicationMessage *indication;

   ret = ooCreateH245Message(call, &ph245msg,
                             T_H245MultimediaSystemControlMessage_indication);
   if(ret != OO_OK)
   {
      OOTRACEERR3("ERROR:Failed to create H245 message for "
                  "RequestChannelCloseRelease message (%s, %s)\n",
                   call->callType, call->callToken);
      return OO_FAILED;
   }
   ph245msg->msgType = OORequestChannelCloseRelease;
   ph245msg->logicalChannelNo = channelNum;

   pctxt = call->msgctxt;
   indication = ph245msg->h245Msg.u.indication;
   indication->t = T_H245IndicationMessage_requestChannelCloseRelease;
   indication->u.requestChannelCloseRelease = (H245RequestChannelCloseRelease*)
                     ASN1MALLOC(pctxt, sizeof(H245RequestChannelCloseRelease));
   if(!indication->u.requestChannelCloseRelease)
   {
      OOTRACEERR3("Error:Failed to allocate memory for "
                  "RequestChannelCloseRelease message. (%s, %s)\n",
                   call->callType, call->callToken);
      ooFreeH245Message(call, ph245msg);
   }

   indication->u.requestChannelCloseRelease->forwardLogicalChannelNumber =
                                                                channelNum;

   OOTRACEDBGA4("Built RequestChannelCloseRelease for %d (%s, %s)\n",
                channelNum, call->callType, call->callToken);
   ret = ooSendH245Msg(call, ph245msg);
   if(ret != OO_OK)
   {
     OOTRACEERR3("Error:Failed to enqueue the RequestChannelCloseRelease to "
                 "outbound queue (%s, %s)\n", call->callType, call->callToken);
   }
   ooFreeH245Message(call, ph245msg);

   return ret;
}
