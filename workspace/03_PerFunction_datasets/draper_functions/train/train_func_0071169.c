sge_give_job(sge_gdi_ctx_class_t *ctx,
                 lListElem *jep, lListElem *jatep, lListElem *master_qep,
                 lListElem *pe, lListElem *hep, monitoring_t *monitor)
{
   const char *rhost;
   int ret = 0;
   int sent_slaves = 0;

   DENTER(TOP_LAYER, "sge_give_job");

   rhost = lGetHost(master_qep, QU_qhostname);
   DPRINTF(("execd host: %s\n", rhost));

   switch (send_slave_jobs(ctx, jep, jatep, pe, monitor)) {
      case -1 : ret = -1;
      case  0 : sent_slaves = 1;
         break;
      case  1 : sent_slaves = 0;
         break;
      default :
         DPRINTF(("send_slave_jobs returned an unknown error code\n"));
         ret = -1;
   }

   if (!sent_slaves) {

      lSetUlong(jatep, JAT_next_pe_task_id, 1);
      ret = send_job(ctx, rhost, jep, jatep, pe, hep, 1);
      MONITOR_MESSAGES_OUT(monitor);
   }

   DRETURN(ret);
}
