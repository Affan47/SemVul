spooling_trigger_handler(sge_gdi_ctx_class_t *ctx, te_event_t anEvent, monitoring_t *monitor)
{
   time_t next_trigger = 0;
   time_t now;
   lList *answer_list = NULL;
   te_event_t ev = NULL;

   DENTER(TOP_LAYER, "deliver_spooling_trigger");


   if (!spool_trigger_context(&answer_list, spool_get_default_context(),
                              te_get_when(anEvent), &next_trigger)) {
      answer_list_output(&answer_list);
   }


   now = time(0);
   if (next_trigger <= now) {
      next_trigger = now + 60;
   }


   ev = te_new_event(next_trigger, te_get_type(anEvent), ONE_TIME_EVENT, 0, 0, NULL);
   te_add_event(ev);
   te_free_event(&ev);

   DEXIT;
   return;
}
