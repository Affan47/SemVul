job_create_task(lListElem *job, lList **answer_list, u_long32 ja_task_id)
{
   lListElem *ja_task = NULL;

   DENTER(TOP_LAYER, "job_create_task");

   if (job != NULL && job_is_ja_task_defined(job, ja_task_id)) {
      ja_task = job_enroll(job, answer_list, ja_task_id);
   }

   DRETURN(ja_task);
}
