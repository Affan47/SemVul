ooCallEstbTimerExpired(void *data)
{

   ooTimerCallback *cbData = (ooTimerCallback*) data;
   OOH323CallData *call = cbData->call;
   OOTRACEINFO3("Call Establishment timer expired. (%s, %s)\n",
                                            call->callType, call->callToken);
   memFreePtr(call->pctxt, cbData);
   if(call->callState < OO_CALL_CLEAR){
      call->callState = OO_CALL_CLEAR;
      call->callEndReason = OO_REASON_LOCAL_CLEARED;
   }

   return OO_OK;
}
