net_ups_open(UPSINFO *ups)
{
   struct driver_data *nid;

   nid = (struct driver_data *)malloc(sizeof(struct driver_data));

   if (nid == NULL) {
      log_event(ups, LOG_ERR, "Out of memory.");
      exit(1);
   }

   memset(nid, 0, sizeof(struct driver_data));
   ups->driver_internal_data = nid;

   initialize_device_data(ups);


   ups->fd = 1;

   return 1;
}
