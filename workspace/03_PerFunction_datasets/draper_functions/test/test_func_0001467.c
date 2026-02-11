qref_list_is_valid(const lList *this_list, lList **answer_list)
{
   bool ret = true;

   DENTER(TOP_LAYER, "qref_list_is_valid");
   if (this_list != NULL) {
      lList *master_cqueue_list = NULL;
      lList *master_hgroup_list = NULL;
      lList *master_centry_list = NULL;

      master_cqueue_list = *(object_type_get_master_list(SGE_TYPE_CQUEUE));
      master_hgroup_list = *(object_type_get_master_list(SGE_TYPE_HGROUP));
      master_centry_list = *(object_type_get_master_list(SGE_TYPE_CENTRY));


      if (centry_list_are_queues_requestable(master_centry_list)) {
         lListElem *qref_elem;


         for_each(qref_elem, this_list) {
            bool found_something = false;
            bool found_matching_qinstance = false;
            const char *qref_pattern = NULL;
            lList *resolved_qref_list = NULL;
            lList *qref_list = NULL;
            lListElem *resolved_qref = NULL;
            qref_resolve_hostname(qref_elem);
            qref_pattern = lGetString(qref_elem, QR_name);

            lAddElemStr(&qref_list, QR_name, qref_pattern, QR_Type);

            qref_list_resolve(qref_list, answer_list, &resolved_qref_list,
                              &found_something, master_cqueue_list,
                              master_hgroup_list, true, true);
            for_each(resolved_qref, resolved_qref_list) {
               const char *resolved_qref_name = NULL;

               resolved_qref_name = lGetString(resolved_qref, QR_name);
               if (cqueue_list_locate_qinstance(master_cqueue_list,
                                                resolved_qref_name) != NULL) {
                  found_matching_qinstance = true;
               }
            }
            lFreeList(&qref_list);
            lFreeList(&resolved_qref_list);
            if (!found_matching_qinstance) {
               ERROR((SGE_EVENT, MSG_QREF_QUNKNOWN_S, qref_pattern == NULL ? "" : qref_pattern));
               answer_list_add(answer_list, SGE_EVENT,
                               STATUS_EUNKNOWN, ANSWER_QUALITY_ERROR);
               ret = false;
            }
         }
      } else {
         ERROR((SGE_EVENT, MSG_QREF_QNOTREQUESTABLE));
         answer_list_add(answer_list, SGE_EVENT,
                         STATUS_EUNKNOWN, ANSWER_QUALITY_ERROR);
         ret = false;
      }
   }
   DRETURN(ret);
}
