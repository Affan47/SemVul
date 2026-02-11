task_ref_get_next_job_entry(void)
{
   sge_task_ref_t *current_entry = task_ref_get_entry(task_ref_job_pos);
   sge_task_ref_t *ret = NULL;
   u_long32 pos = task_ref_job_pos;

   DENTER(BASIS_LAYER, "task_ref_get_next_job_entry");
   if (current_entry != NULL) {
      u_long32 current_job_number = current_entry->job_number;

      while (++pos < task_ref_entries) {
         sge_task_ref_t *next_entry = task_ref_get_entry(pos);

         if (next_entry != NULL &&
             current_job_number != next_entry->job_number) {
            task_ref_job_pos = pos;
            ret = next_entry;
            break;
         }
      }
   }
   DEXIT;
   return ret;
}
