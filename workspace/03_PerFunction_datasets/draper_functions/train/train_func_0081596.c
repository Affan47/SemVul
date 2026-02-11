spool_type_add_rule(lList **answer_list, lListElem *spool_type,
                    const lListElem *rule, lBool is_default)
{
   lListElem *ep = NULL;

   DENTER(TOP_LAYER, "spool_type_add_rule");
   PROF_START_MEASUREMENT(SGE_PROF_SPOOLING);

   if(spool_type == NULL) {
      answer_list_add_sprintf(answer_list, STATUS_EUNKNOWN,
                              ANSWER_QUALITY_ERROR,
                              MSG_SPOOL_NOVALIDSPOOLTYPE_S, SGE_FUNC);
   } else if(rule == NULL) {
      answer_list_add_sprintf(answer_list, STATUS_EUNKNOWN,
                              ANSWER_QUALITY_ERROR, MSG_SPOOL_NOVALIDRULE_S,
                              SGE_FUNC);
   } else if(is_default && spool_type_search_default_rule(spool_type) != NULL) {
      answer_list_add_sprintf(answer_list, STATUS_EUNKNOWN,
                              ANSWER_QUALITY_ERROR,
                              MSG_SPOOL_TYPEALREADYHASDEFAULTRULE_S,
                              lGetString(spool_type, SPT_name));
   } else {
      lList *lp;


      ep = lCreateElem(SPTR_Type);
      lSetBool(ep, SPTR_default, is_default);
      lSetString(ep, SPTR_rule_name, lGetString(rule, SPR_name));
      lSetRef(ep, SPTR_rule, (void *)rule);


      lp = lGetList(spool_type, SPT_rules);
      if (lp == NULL) {
         lp = lCreateList("spooling object type rules", SPTR_Type);
         lSetList(spool_type, SPT_rules, lp);
      }

      lAppendElem(lp, ep);
   }

   PROF_STOP_MEASUREMENT(SGE_PROF_SPOOLING);
   DRETURN(ep);
}
