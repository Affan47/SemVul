ooSendH245UserInputIndication_signal
   (OOH323CallData *call, const char *data)
{
   int ret=0;
   H245IndicationMessage* indication=NULL;
   H245Message *ph245msg=NULL;

   OOCTXT *pctxt=call->msgctxt;

   ret = ooCreateH245Message
      (call, &ph245msg, T_H245MultimediaSystemControlMessage_indication);

   if (ret != OO_OK) {
      OOTRACEERR3("Error:H245 message creation failed for - H245UserInput"
                  "Indication_signal (%s, %s)\n",call->callType,
                  call->callToken);
      return OO_FAILED;
   }
   ph245msg->msgType = OOUserInputIndication;
   indication = ph245msg->h245Msg.u.indication;

   indication->t = T_H245IndicationMessage_userInput;
   indication->u.userInput =
      (H245UserInputIndication*)
      memAllocZ (pctxt, sizeof(H245UserInputIndication));

   if(!indication->u.userInput)
   {
      OOTRACEERR3("Error: Memory - ooH245UserInputIndication_signal - "
                  " userInput (%s, %s)\n", call->callType, call->callToken);
      ooFreeH245Message(call, ph245msg);
      return OO_FAILED;
   }
   indication->u.userInput->t = T_H245UserInputIndication_signal;
   indication->u.userInput->u.signal = (H245UserInputIndication_signal*)
                      memAllocZ(pctxt, sizeof(H245UserInputIndication_signal));
   indication->u.userInput->u.signal->signalType = (ASN1IA5String)
                                              memAlloc(pctxt, strlen(data)+1);
   if(!indication->u.userInput->u.signal ||
      !indication->u.userInput->u.signal->signalType)
   {
      OOTRACEERR3("Error: Memory - ooH245UserInputIndication_signal - "
                  "signal (%s, %s).\n", call->callType, call->callToken);
      ooFreeH245Message(call, ph245msg);
      return OO_FAILED;
   }
   strcpy(*(char**)&indication->u.userInput->u.signal->signalType, data);
   OOTRACEDBGA3 ("Built UserInputIndication_signal (%s, %s)\n",
                 call->callType, call->callToken);

   ret = ooSendH245Msg (call, ph245msg);

   if (ret != OO_OK) {
      OOTRACEERR3
         ("Error:Failed to enqueue UserInputIndication_signal "
          "message to outbound queue.(%s, %s)\n", call->callType,
          call->callToken);
   }

   ooFreeH245Message (call, ph245msg);
   return ret;
}
