japi_synchronize_jobids_retry(const char *job_ids[], bool dispose)
{
   int i;
   lListElem *japi_job;
   lList *not_yet_finished;

   DENTER(TOP_LAYER, "japi_synchronize_jobids_retry");


   for (i=0; job_ids[i] != NULL; i++) {
      u_long32 jobid, taskid;
      bool is_array;


      japi_parse_jobid(job_ids[i], &jobid, &taskid, &is_array, NULL);

      japi_job = lGetElemUlong(Master_japi_job_list, JJ_jobid, jobid);

      if (japi_job == NULL) {
         DPRINTF(("synchronized with "sge_u32"."sge_u32"\n", jobid, taskid));
         continue;
      }

      not_yet_finished = lGetList(japi_job, JJ_not_yet_finished_ids);
      if (not_yet_finished && range_list_is_id_within(not_yet_finished, taskid)) {
         DPRINTF(("job "sge_u32"."sge_u32" is a still unfinished task\n", jobid, taskid));
         DRETURN(JAPI_WAIT_UNFINISHED);
      }

      DPRINTF(("synchronized with "sge_u32"."sge_u32"\n", jobid, taskid));
      if (dispose) {

         lDelSubUlong(japi_job, JJAT_task_id, taskid, JJ_finished_tasks);
         DPRINTF(("dispose job finish information for job "sge_u32" task "sge_u32"\n", jobid, taskid));
         if (!lGetList(japi_job, JJ_finished_tasks) && !not_yet_finished) {

            lRemoveElem(Master_japi_job_list, &japi_job);
         }
      }
   }

   DRETURN(JAPI_WAIT_ALLFINISHED);
}
