ooCapabilityCheckCompatibility_Video
   (OOH323CallData *call, ooH323EpCapability* epCap,
    H245VideoCapability* videoCap, int dir)
{
   switch(videoCap->t)
   {
   case T_H245VideoCapability_h263VideoCapability:
      return ooCapabilityCheckCompatibility_H263Video(call, epCap,
                                                              videoCap, dir);
   default:
     OOTRACEDBGC3("ooCapabilityCheckCompatibility_Video - Unsupported video "
                  "capability. (%s, %s)\n", call->callType, call->callToken);
   }
   return FALSE;
}
