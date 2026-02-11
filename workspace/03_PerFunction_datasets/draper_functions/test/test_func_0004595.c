RaTimeoutArgusStore (struct ArgusRecordStore *store)
{
   struct ArgusRecord *argus;
   int i, retn = 0;

   if (store != NULL) {
      if (store->status & RA_MODIFIED)
         retn = RaSendArgusRecord(store);

      if (store->rahtblhdr)
         RaRemoveHashEntry (store->rahtblhdr->htable, store->rahtblhdr);

      for (i = 0; i < RaHistoTimeSeries + 1; i++) {
         struct ArgusRecordData *data = NULL;

         if ((data = store->data[i]) != NULL) {
            if ((argus = data->argus) != NULL) {
               RaRemoveArgusRecord(argus);
               ArgusFree (argus);
               data->argus = NULL;
            }
            ArgusFree(data);
            store->data[i] = NULL;
         }
      }

      if (store->queue != NULL)
         RaDeleteQueue(store->queue);

      ArgusFree (store->data);
      ArgusFree (store);
      RaAllocArgusRecordStore--;
   }

#ifdef ARGUSDEBUG
   ArgusDebug (6, "RaTimeoutArgusStore: 0x%x returning %d\n", store, retn);
#endif

   return (retn);
}
