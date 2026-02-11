qstat_stdout_pending_jobs_started(qstat_handler_t *handler, lList **alpp)
{
   qstat_env_t *qstat_env = handler->qstat_env;
   qstat_stdout_ctx_t *ctx = (qstat_stdout_ctx_t*)handler->ctx;

   DENTER(TOP_LAYER, "qstat_stdout_pending_jobs_started");

   ctx->last_job_id = 0;
   sge_printf_header((qstat_env->full_listing & QSTAT_DISPLAY_FULL) |
                     (qstat_env->full_listing & QSTAT_DISPLAY_PENDING),
                     (qstat_env->full_listing & QSTAT_DISPLAY_EXTENDED) == QSTAT_DISPLAY_EXTENDED);
   DEXIT;
   return 0;
}
