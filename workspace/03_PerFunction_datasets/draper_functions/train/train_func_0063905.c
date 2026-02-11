te_scan_table_and_deliver(sge_gdi_ctx_class_t *ctx, te_event_t anEvent, monitoring_t *monitor)
{
   int i = 0;
   te_handler_t handler = NULL;

   DENTER(EVENT_LAYER, "te_scan_table_and_deliver");

   DPRINTF(("%s: event (t:"sge_u32" w:"sge_u32" m:"sge_u32" s:%s)\n", EVENT_FRMT(anEvent)));

   sge_mutex_lock("handler_table_mutex", SGE_FUNC, __LINE__, &Handler_Tbl.mutex);

   for(i = 0; i < Handler_Tbl.num; i++)
   {
      te_type_t type = Handler_Tbl.list[i].type;

      if (type == anEvent->type) {
         handler = Handler_Tbl.list[i].handler;
         break;
      }
   }

   sge_mutex_unlock("handler_table_mutex", SGE_FUNC, __LINE__, &Handler_Tbl.mutex);

   if (handler != NULL) {
      handler(ctx, anEvent, monitor);
   } else {
      WARNING((SGE_EVENT, MSG_SYSTEM_RECEIVEDUNKNOWNEVENT_I, anEvent->type ));
   }

   if (RECURRING_EVENT == anEvent->mode)
   {
      anEvent->when = time(NULL) + anEvent->interval;

      DPRINTF(("%s: reccuring event (t:"sge_u32" w:"sge_u32" m:"sge_u32" s:%s)\n", EVENT_FRMT(anEvent)));

      te_add_event(anEvent);
   }

   DEXIT;
   return;
}
