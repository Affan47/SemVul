ja_task_verify_granted_destin_identifier(const lListElem *ep, lList **answer_list)
{
   bool ret = true;

   DENTER(TOP_LAYER, "ja_task_verify_granted_destin_identifier");

   if (ep == NULL) {
      answer_list_add_sprintf(answer_list, STATUS_ESYNTAX, ANSWER_QUALITY_ERROR,
                              MSG_NULLELEMENTPASSEDTO_S, SGE_FUNC);
      ret = false;
   }

   if (ret) {
      ret = qinstance_verify_full_name(answer_list, lGetString(ep, JG_qname));
   }

   if (ret) {
      ret = verify_host_name(answer_list, lGetHost(ep, JG_qhostname));
   }

   if (ret) {
      ret = object_verify_ulong_not_null(ep, answer_list, JG_slots);
   }

   if (ret) {
      const lListElem *queue = lGetObject(ep, JG_queue);

      if (queue != NULL) {
         ret = qinstance_verify(queue, answer_list);
      }
   }

   DRETURN(ret);
}
