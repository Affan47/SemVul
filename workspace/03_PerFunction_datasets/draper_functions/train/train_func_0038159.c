ptf_process_job_ticket_list(lList *job_ticket_list)
{
   lListElem *jte, *job;

   DENTER(TOP_LAYER, "ptf_process_job_ticket_list");


   for_each(jte, job_ticket_list) {


      lSetString(jte, JB_script_file, "dummy");

      job = ptf_process_job(0, NULL, jte,
                            lGetUlong(lFirst(lGetList(jte, JB_ja_tasks)),
                            JAT_task_number));
      if (job) {

         lSetDouble(job, JL_usage, MAX(PTF_MIN_JOB_USAGE,
                                       lGetDouble(job, JL_usage) * 0.1));

         lSetDouble(job, JL_curr_pri, 0);
      }
   }

   DEXIT;
   return 0;
}
