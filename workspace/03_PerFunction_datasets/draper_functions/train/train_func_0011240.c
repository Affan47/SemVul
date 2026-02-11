job_write_spool_file(lListElem *job, u_long32 ja_taskid,
                         const char *pe_task_id,
                         sge_spool_flags_t flags)
{
   int ret = 0;
   int report_long_delays = flags & SPOOL_WITHIN_EXECD;
   u_long32 start = 0;

   DENTER(TOP_LAYER, "job_write_spool_file");

   if (report_long_delays) {
      start = sge_get_gmt();
   }

   if (job_has_to_spool_one_file(job, *object_type_get_master_list(SGE_TYPE_PE),
                                        flags)) {
      ret = job_write_as_single_file(job, ja_taskid, flags);
   } else {
      if (!(flags & SPOOL_ONLY_JATASK) && !(flags & SPOOL_ONLY_PETASK)) {
         ret = job_write_common_part(job, ja_taskid, flags);
      }
      if (!ret && !(flags & SPOOL_IGNORE_TASK_INSTANCES)) {
         ret = job_write_ja_task_part(job, ja_taskid, pe_task_id, flags);
      }
   }

   if (report_long_delays) {
      u_long32 time = sge_get_gmt() - start;
      if (time > 30) {

         WARNING((SGE_EVENT, MSG_CONFIG_JOBSPOOLINGLONGDELAY_UUI,
         sge_u32c(lGetUlong(job, JB_job_number)), sge_u32c(ja_taskid), (int)time));
      }
   }

   DRETURN(ret);
}
