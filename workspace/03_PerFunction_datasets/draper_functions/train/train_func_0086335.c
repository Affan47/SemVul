RaProcessManRecord (struct ArgusRecord *argus)
{
   struct ArgusRecordStore *srv = NULL;

   if ((srv = RaNewArgusStore(argus)) != NULL) {
      srv->startime = argus->argus_far.time.start;
      srv->lasttime = argus->argus_far.time.last;

      srv->status |= RA_MODIFIED;
      if ((srv->data[RaThisActiveIndex] = RaNewArgusData(argus)) != NULL) {
         srv->data[RaThisActiveIndex]->status |= RA_MODIFIED;


      }

      RaDeleteArgusStore(srv);
   }

#ifdef ARGUSDEBUG
   ArgusDebug (2, "RaProcessManRecord (0x%x): done\n", argus);
#endif
}
