sge_mirror_process_events(sge_evc_class_t *evc)
{
   lList *event_list = NULL;
   sge_mirror_error ret = SGE_EM_OK;
   static int test_debug = 0;

   DENTER(TOP_LAYER, "sge_mirror_process_events");

   if (evc && evc->ec_get(evc, &event_list, false)) {
      if (event_list != NULL) {
         ret = sge_mirror_process_event_list(evc, event_list);
         lFreeList(&event_list);
      }
   } else {
      WARNING((SGE_EVENT, MSG_MIRROR_QMASTERALIVETIMEOUTEXPIRED));
      evc->ec_mark4registration(evc);
      ret = SGE_EM_TIMEOUT;
   }

   if (mir_get_produce_qmaster_alive_timeout()) {
      test_debug++;
      if (test_debug > 3) {
         test_debug = 0;
         WARNING((SGE_EVENT, MSG_MIRROR_QMASTERALIVETIMEOUTEXPIRED));
         evc->ec_mark4registration(evc);
         ret = SGE_EM_TIMEOUT;
      }
   }

   DRETURN(ret);
}
