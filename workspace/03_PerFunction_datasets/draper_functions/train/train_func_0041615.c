job_delete_not_enrolled_ja_task(lListElem *job, lList **answer_list,
                                     u_long32 ja_task_number)
{
   const int attributes = 5;
   const int attribute[] = {JB_ja_n_h_ids, JB_ja_u_h_ids, JB_ja_o_h_ids,
                            JB_ja_s_h_ids, JB_ja_a_h_ids};
   int i;

   DENTER(TOP_LAYER, "job_delete_not_enrolled_ja_task");
   for (i = 0; i < attributes; i++) {
      object_delete_range_id(job, answer_list, attribute[i], ja_task_number);
   }
   DRETURN_VOID;
}
