sge_task_depend_get_range(lListElem **range, lList **alpp,
                              const lListElem *pre_jep,
                              const lListElem *suc_jep, u_long32 task_id)
{
   u_long32 a0, a1, b0, b1, sa, sb, rmin, rmax;

   DENTER(TOP_LAYER, "sge_task_depend_get_range");

   if (range == NULL ||
         pre_jep == NULL ||
         suc_jep == NULL) {
      DRETURN(STATUS_EUNKNOWN);
   }

   job_get_submit_task_ids(pre_jep, &a0, &a1, &sa);
   job_get_submit_task_ids(suc_jep, &b0, &b1, &sb);


   if (!sge_task_depend_is_same_range(pre_jep, suc_jep)) {
      DRETURN(STATUS_EUNKNOWN);
   }


   if (task_id < b0 || ((task_id - b0) % sb) != 0) {
      DRETURN(STATUS_EUNKNOWN);
   }


   task_depend(&rmin, &rmax, a0, sa, sb, task_id);


   if (rmin < a0 || rmax > a1) {
      DRETURN(STATUS_EUNKNOWN);
   }


   if (*range == NULL) {
      *range = lCreateElem(RN_Type);
      if (*range == NULL) {
         DRETURN(STATUS_EUNKNOWN);
      }
   }

   range_set_all_ids(*range, rmin, rmax, sa);

   DRETURN(0);
}
