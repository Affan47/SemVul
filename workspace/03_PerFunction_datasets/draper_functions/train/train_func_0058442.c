jgdi_qstat_job_hard_resource(job_handler_t *handler, const char* name, const char* value, double uc, lList **alpp) {
   jgdi_job_ctx_t *ctx = (jgdi_job_ctx_t*)handler->ctx;
   jgdi_result_t ret = JGDI_SUCCESS;
   DENTER(JGDI_LAYER, "jgdi_qstat_job_hard_resource");

   ret = JobSummaryImpl_addHardRequest(ctx->jni_env, ctx->job, name, value, (jdouble)uc, alpp);

   ctx->result = ret;
   if (ret != JGDI_SUCCESS) {
      DRETURN(-1);
   }
   DRETURN(0);
}
