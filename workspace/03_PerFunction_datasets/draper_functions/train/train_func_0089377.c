qrstat_report_ar_node_ulong_unknown(qrstat_report_handler_t* handler, qrstat_env_t *qrstat_env, lList **alpp,
                            const char *name, u_long32 value)
{
   bool ret = true;
   FILE *out = (FILE*)handler->ctx;

   DENTER(TOP_LAYER, "qrstat_report_ar_node_ulong_unknown");
   if (qrstat_env->header_printed) {
      fprintf(out, ", ");
   } else {
      qrstat_env->header_printed = true;
   }
   fprintf(out, sge_U32CFormat, sge_u32c(value));

   DRETURN(ret);
}
