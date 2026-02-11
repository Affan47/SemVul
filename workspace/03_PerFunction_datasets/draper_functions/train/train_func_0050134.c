RaPushQueue(struct RaQueueStruct *queue, struct ArgusQueueHeader *obj)
{
   int retn = 0;

   if ((retn = RaAddToQueue (queue, obj)) > 0)
      queue->start = queue->start->prv;

#ifdef ARGUSDEBUG
   ArgusDebug (7, "RaPushQueue (0x%x, 0x%x) returning\n", queue, obj);
#endif
}
