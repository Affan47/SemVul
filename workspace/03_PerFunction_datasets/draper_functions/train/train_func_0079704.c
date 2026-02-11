resend_signal_event(sge_gdi_ctx_class_t *ctx, te_event_t anEvent, monitoring_t *monitor)
{
   lListElem *qep, *jep, *jatep;
   u_long32 jobid = te_get_first_numeric_key(anEvent);
   u_long32 jataskid = te_get_second_numeric_key(anEvent);
   const char* queue = te_get_alphanumeric_key(anEvent);

   DENTER(TOP_LAYER, "resend_signal_event");

   MONITOR_WAIT_TIME(SGE_LOCK(LOCK_GLOBAL, LOCK_WRITE), monitor);

   if (queue == NULL) {
      if (!(jep = job_list_locate(*(object_type_get_master_list(SGE_TYPE_JOB)), jobid)) || !(jatep=job_search_task(jep, NULL, jataskid)))
      {
         ERROR((SGE_EVENT, MSG_EVE_RESENTSIGNALTASK_UU, sge_u32c(jobid), sge_u32c(jataskid)));
         SGE_UNLOCK(LOCK_GLOBAL, LOCK_WRITE);
         DEXIT;
         return;
      }

      if ((qep = cqueue_list_locate_qinstance(*(object_type_get_master_list(SGE_TYPE_CQUEUE)), lGetString(jatep, JAT_master_queue)))) {
         sge_signal_queue(ctx, lGetUlong(jatep, JAT_pending_signal), qep, jep, jatep, monitor);
      }
   } else {
      if (!(qep = cqueue_list_locate_qinstance(*(object_type_get_master_list(SGE_TYPE_CQUEUE)), queue))) {
         ERROR((SGE_EVENT, MSG_EVE_RESENTSIGNALQ_S, queue));
         SGE_UNLOCK(LOCK_GLOBAL, LOCK_WRITE);
         sge_free((char *)queue);
         DEXIT;
         return;
      }

      sge_signal_queue(ctx, lGetUlong(qep, QU_pending_signal), qep, NULL, NULL, monitor);
   }

   sge_free((char *)queue);

   SGE_UNLOCK(LOCK_GLOBAL, LOCK_WRITE);

   DEXIT;
   return;
}
