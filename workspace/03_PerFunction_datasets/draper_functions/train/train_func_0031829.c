ArgusProcessQueue(struct ArgusQueueStruct *queue, unsigned char status)
{
   struct ArgusFlowStruct *obj = NULL;
   int cnt = 0;

   switch (status) {
      case ARGUS_STOP:
      case ARGUS_SHUTDOWN:
         while (queue->count) {
            if ((obj = ArgusPopQueue(queue)) != NULL) {
               if (obj->FragDSRBuffer != NULL) {
                  if (ArgusUpdateParentFlow(obj)) {
                     ArgusDeleteObject (obj);
                     obj = NULL;
                  }
               }
               if (obj) {
                  if ((obj->state.ofragcnt) && (!(obj->qhdr.status & ARGUS_PROCESS_NEXT_PASS))) {
                     obj->qhdr.status |= ARGUS_PROCESS_NEXT_PASS;
                     ArgusAddToQueue(queue, obj);

                  } else {
                     ArgusSendFlowRecord(obj, status);
                     ArgusDeleteObject (obj);
                  }
               }
            }
         }
         break;

      default:
         if (queue->count > 0) {
            cnt = ((queue->count == 1 ) ? queue->count :
                  ((queue->count < ARGUS_MINQSCAN) ? ((queue->count / 4) + 2):
                  ((queue->count < ARGUS_TR2QSCAN) ? (queue->count / 8) :
                  ((queue->count < ARGUS_MAXQSCAN) ? ARGUS_TR1QSCAN :
                    queue->count / 128))));
            if (cnt > 1) {
               while (cnt--) {
                  if ((obj = ArgusPopQueue(queue)) != NULL) {
                     if (ArgusCheckTimeout(obj))
                        ArgusTimeOut(obj);
                     else
                        ArgusAddToQueue(queue, obj);
                  }
               }
            } else {
               if ((obj = ArgusFrontQueue(queue)) != NULL) {
                  if (ArgusCheckTimeout(obj)) {
                     ArgusPopQueue(queue);
                     ArgusTimeOut(obj);
                  }
               }
            }
         }

         break;
   }

#ifdef ARGUSDEBUG
   ArgusDebug (8, "ArgusProcessQueue (0x%x, %d) returning\n", queue, status);
#endif
}
