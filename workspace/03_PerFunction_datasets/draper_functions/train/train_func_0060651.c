spool_read_list(lList **answer_list, const lListElem *context,
                lList **list, const sge_object_type object_type)
{
   bool ret = false;

   DENTER(TOP_LAYER, "spool_read_list");
   PROF_START_MEASUREMENT(SGE_PROF_SPOOLING);

   if (context == NULL) {
      answer_list_add_sprintf(answer_list, STATUS_EUNKNOWN,
                              ANSWER_QUALITY_ERROR, MSG_SPOOL_NOVALIDCONTEXT_S,
                              SGE_FUNC);
   } else {
      lListElem *type;


      type = spool_context_search_type(context, object_type);
      if (type == NULL) {
         answer_list_add_sprintf(answer_list, STATUS_EUNKNOWN,
                                 ANSWER_QUALITY_ERROR,
                                 MSG_SPOOL_UNKNOWNOBJECTTYPEINCONTEXT_SS,
                                 object_type_get_name(object_type),
                                 lGetString(context, SPC_name));
      } else {
         lListElem *rule;


         rule = spool_type_search_default_rule(type);
         if (rule == NULL) {
            answer_list_add_sprintf(answer_list, STATUS_EUNKNOWN,
                                    ANSWER_QUALITY_ERROR,
                                    MSG_SPOOL_NODEFAULTRULEFORTYPEINCONTEXT_SS,
                                    object_type_get_name(object_type),
                                    lGetString(context, SPC_name));
         } else {
            spooling_list_func func;


            func = (spooling_list_func)lGetRef(rule, SPR_list_func);
            if (func == NULL) {
               answer_list_add_sprintf(answer_list, STATUS_EUNKNOWN,
                                       ANSWER_QUALITY_ERROR,
                                       MSG_SPOOL_CORRUPTRULEINCONTEXT_SSS,
                                       lGetString(rule, SPR_name),
                                       lGetString(context, SPC_name),
                                       SGE_FUNC);
            } else {
               ret = func(answer_list, type, rule, list, object_type);
            }
         }
      }
   }

   PROF_STOP_MEASUREMENT(SGE_PROF_SPOOLING);
   DRETURN(ret);
}
