sge_event_master_process_ack(lListElem *request, monitoring_t *monitor)
{
   lListElem *client;
   u_long32 event_client_id;

   DENTER(TOP_LAYER, "sge_event_master_process_ack");

   event_client_id = lGetUlong(request, EVR_event_client_id);

   sge_mutex_lock("event_master_mutex", SGE_FUNC, __LINE__, &Event_Master_Control.mutex);

   client = get_event_client(event_client_id);

   if (client == NULL) {
      ERROR((SGE_EVENT, MSG_EVE_UNKNOWNEVCLIENT_US, sge_u32c(event_client_id), "process acknowledgements"));
   } else {
      u_long32 event_number = lGetUlong(request, EVR_event_number);
      u_long32 timestamp = lGetUlong(request, EVR_timestamp);
      int res = 0;
      lList *list = lGetList(client, EV_events);

      res = purge_event_list(list, event_number);

      MONITOR_EDT_ACK(monitor);
      if (res > 0) {
         DPRINTF(("%s: purged %d acknowledged events\n", SGE_FUNC, res));
      }

      lSetUlong(client, EV_last_heard_from, timestamp);

      switch (lGetUlong(client, EV_busy_handling)) {
         case EV_BUSY_UNTIL_ACK:
         case EV_THROTTLE_FLUSH:
            lSetUlong(client, EV_busy, 0);
            break;
         default:
            break;
      }
   }

   sge_mutex_unlock("event_master_mutex", SGE_FUNC, __LINE__, &Event_Master_Control.mutex);
   DRETURN_VOID;
}
