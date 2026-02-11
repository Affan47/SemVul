sge_job_remove_enforce_limit_trigger(u_long32 job_id, u_long32 ja_task_id)
{
   lList *master_cqueue_list = *(object_type_get_master_list(SGE_TYPE_CQUEUE));
   lList *master_job_list = *(object_type_get_master_list(SGE_TYPE_JOB));
   lList *master_pe_list = *(object_type_get_master_list(SGE_TYPE_PE));
   lListElem *job = job_list_locate(master_job_list, job_id);
   lListElem *ja_task = job_search_task(job, NULL, ja_task_id);
   bool delete_trigger = false;

   DENTER(TOP_LAYER, "sge_job_remove_enforce_limit_trigger");


   if (job != NULL && ja_task != NULL) {
      if (job_is_tight_parallel(job, master_pe_list)) {
         lList *pe_tasks = lGetList(ja_task, JAT_task_list);
         lListElem *pe_task;
         bool all_are_known = true;

         for_each (pe_task, pe_tasks) {
            lList *gdil = NULL;
            lListElem *gdil_ep;
            lListElem *qinstance;

            gdil = lGetList(pe_task, PET_granted_destin_identifier_list);
            gdil_ep = lFirst(gdil);
            if (gdil_ep != NULL) {
               qinstance = cqueue_list_locate_qinstance(master_cqueue_list, lGetString(gdil_ep, JG_qname));

               if (qinstance != NULL) {
                  if (qinstance_state_is_unknown(qinstance) == true) {
                     lSetBool(pe_task, PET_do_contact, false);
                     all_are_known = false;
                  } else {
                     lSetBool(pe_task, PET_do_contact, true);
                  }
               }
            }
         }
         if (all_are_known) {
            delete_trigger = true;
         }
      } else {
         delete_trigger = true;
      }
   }


   if (delete_trigger) {
      INFO((SGE_EVENT, MSG_JOB_DELJOBTRIGGER_UU, sge_u32c(job_id), sge_u32c(ja_task_id)));
      te_delete_one_time_event(TYPE_ENFORCE_LIMIT_EVENT, job_id, ja_task_id, NULL);
   }

   DRETURN_VOID;
}
