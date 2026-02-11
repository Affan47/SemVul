qinstance_list_verify_execd_job(const lList *queue_list, lList **answer_list)
{

   DENTER(TOP_LAYER, "qinstance_list_verify_execd_job");

   if (queue_list == NULL) {
      answer_list_add_sprintf(answer_list, STATUS_ESYNTAX, ANSWER_QUALITY_ERROR,
                              MSG_NULLELEMENTPASSEDTO_S, SGE_FUNC);
      DRETURN(false);
   } else {
      const lListElem *qep;

      for_each (qep, queue_list) {
         if (!qinstance_verify(qep, answer_list)) {
            DRETURN(false);
         }
      }
   }

   DRETURN(true);
}
