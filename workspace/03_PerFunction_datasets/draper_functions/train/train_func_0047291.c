sge_evc_class_create(sge_gdi_ctx_class_t *sge_gdi_ctx, ev_registration_id reg_id,
                     lList **alpp, const char *name)
{
   sge_evc_class_t *ret = (sge_evc_class_t *)sge_malloc(sizeof(sge_evc_class_t));
   sge_evc_t *sge_evc = NULL;
   bool is_qmaster_internal = false;

   DENTER(EVC_LAYER, "sge_evc_class_create");

   if (!ret) {
      answer_list_add_sprintf(alpp, STATUS_EMALLOC, ANSWER_QUALITY_ERROR, MSG_MEMORY_MALLOCFAILED);
      DRETURN(NULL);
   }


   is_qmaster_internal = sge_gdi_ctx->is_qmaster_internal_client(sge_gdi_ctx);

   DPRINTF(("creating %s event client context\n", is_qmaster_internal ? "internal" : "external"));

   if (is_qmaster_internal == true) {
      ret->ec_register = ec2_register_local;
      ret->ec_deregister = ec2_deregister_local;
      ret->ec_commit = ec2_commit_local;
      ret->ec_get = ec2_get_local;
      ret->ec_signal = ec2_signal_local;
      ret->ec_wait = ec2_wait_local;
   } else {
      ret->ec_register = ec2_register;
      ret->ec_deregister = ec2_deregister;
      ret->ec_commit = ec2_commit;
      ret->ec_get = ec2_get;
      ret->ec_signal = ec2_signal;
      ret->ec_wait = ec2_wait;
   }

   ret->get_gdi_ctx = get_gdi_ctx;
   ret->ec_is_initialized = ec2_is_initialized;
   ret->ec_get_event_client = ec2_get_event_client;
   ret->ec_subscribe = ec2_subscribe;
   ret->ec_subscribe_all = ec2_subscribe_all;
   ret->ec_unsubscribe = ec2_unsubscribe;
   ret->ec_unsubscribe_all = ec2_unsubscribe_all;
   ret->ec_get_flush = ec2_get_flush;
   ret->ec_set_flush = ec2_set_flush;
   ret->ec_unset_flush = ec2_unset_flush;
   ret->ec_subscribe_flush = ec2_subscribe_flush;
   ret->ec_mod_subscription_where = ec2_mod_subscription_where;
   ret->ec_set_edtime = ec2_set_edtime;
   ret->ec_get_edtime = ec2_get_edtime;
   ret->ec_set_busy_handling = ec2_set_busy_handling;
   ret->ec_get_busy_handling = ec2_get_busy_handling;
   ret->ec_set_flush_delay = ec2_set_flush_delay;
   ret->ec_get_flush_delay = ec2_get_flush_delay;
   ret->ec_set_busy = ec2_set_busy;
   ret->ec_get_busy = ec2_get_busy;
   ret->ec_set_session = ec2_set_session;
   ret->ec_get_session = ec2_get_session;
   ret->ec_get_id = ec2_get_id;
   ret->ec_commit_multi = ec2_commit_multi;
   ret->ec_mark4registration = ec2_mark4registration;
   ret->ec_need_new_registration = ec2_need_new_registration;
   ret->ec_ack = ec2_ack;
   ret->ec_evco_triggered = ec2_evco_triggered;
   ret->ec_evco_exit = ec2_evco_exit;

   ret->sge_evc_handle = NULL;

   sge_evc = (sge_evc_t*)sge_malloc(sizeof(sge_evc_t));
   if (!sge_evc) {
      answer_list_add_sprintf(alpp, STATUS_EMALLOC, ANSWER_QUALITY_ERROR, MSG_MEMORY_MALLOCFAILED);
      sge_evc_class_destroy(&ret);
      DRETURN(NULL);
   }
   sge_evc->need_register = true;
   sge_evc->ec = NULL;
   sge_evc->ec_reg_id = 0;
   sge_evc->next_event = 1;

   ret->sge_evc_handle = sge_evc;

   if (!sge_evc_setup(ret, sge_gdi_ctx, reg_id, name)) {
      sge_evc_class_destroy(&ret);
      DRETURN(NULL);
   }

   DRETURN(ret);
}
