jgdi_report_job_double_value(qhost_report_handler_t *report_handler, const char *qname, const char *job_name, const char *key, double value, lList **alpp)
{
   jgdi_report_handler_t* ctx = (jgdi_report_handler_t*)report_handler->ctx;
   JNIEnv *env = ctx->env;

   DENTER(JGDI_LAYER, "jgdi_report_job_double_value");

   DPRINTF(("jgdi_report_job_double_value: queue(%s), job(%s), key(%s), value(%f)\n", qname, job_name, key, value));

   if (!strcmp(key, "priority")) {
      if (JobInfoImpl_setPriority(env, ctx->job_info, value, alpp) != JGDI_SUCCESS) {
         goto error;
      }
   }

   DRETURN(QHOST_SUCCESS);

error:
   DRETURN(QHOST_ERROR);
}
