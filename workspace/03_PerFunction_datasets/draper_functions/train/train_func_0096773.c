ArgusCheckTimeout(struct ArgusFlowStruct *obj)
{
   int retn = 0;
   unsigned int lapseTime;
   struct timeval *tvp = NULL, thisTimeout;

   if (obj->qhdr.lasttime.tv_sec > 0) {
      lapseTime = obj->qhdr.lasttime.tv_sec + obj->ArgusTimeout;

      if (((ArgusGlobalTime.tv_sec > lapseTime) || ((ArgusGlobalTime.tv_sec == lapseTime) &&
          (ArgusGlobalTime.tv_usec > obj->qhdr.lasttime.tv_usec))) && (!(obj->state.ofragcnt)))
         retn++;

      if ((tvp = getArgusFarReportInterval ()) != NULL) {
         thisTimeout.tv_sec  = tvp->tv_sec  + obj->qhdr.logtime.tv_sec;
         thisTimeout.tv_usec = tvp->tv_usec + obj->qhdr.logtime.tv_usec;

         if (thisTimeout.tv_usec >= 1000000) {
            thisTimeout.tv_sec++;
            thisTimeout.tv_usec -= 1000000;
         }

         if ((ArgusGlobalTime.tv_sec > thisTimeout.tv_sec) || ((ArgusGlobalTime.tv_sec == thisTimeout.tv_sec) &&
             (ArgusGlobalTime.tv_usec > thisTimeout.tv_usec)))

            ArgusSendFlowRecord (obj, ARGUS_STATUS);
      }

   } else
      obj->qhdr.lasttime = ArgusGlobalTime;

#ifdef ARGUSDEBUG
      ArgusDebug (7, "ArgusCheckTimeout (0x%x) returning %d\n", obj, retn);
#endif

   return (retn);
}
