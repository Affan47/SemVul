jgdi_qstat_queue_started(qstat_handler_t *handler, const char* qname, lList **alpp) {
   qstat_ctx_t *ctx = (qstat_ctx_t*)handler->ctx;
   JNIEnv *env = ctx->jni_env;
   jgdi_result_t ret = JGDI_SUCCESS;

   DENTER(JGDI_LAYER, "jgdi_qstat_queue_started");

   jgdi_log_printf(env, JGDI_QSTAT_LOGGER, FINEST,
                   "queue instance %s started", qname);

   ret = QueueInstanceSummaryImpl_init(env, &ctx->queue_instance_summary, alpp);
   if (ret != JGDI_SUCCESS) {
      goto error;
   }

   if ((ret = QueueInstanceSummaryImpl_setName(env, ctx->queue_instance_summary, qname, alpp)) != JGDI_SUCCESS) {
      goto error;
   }

error:
   ctx->result = ret;
   if(ret != JGDI_SUCCESS) {
      DRETURN(-1);
   }
   DRETURN(0);
}
