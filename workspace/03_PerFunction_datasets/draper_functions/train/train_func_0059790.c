parallel_check_and_debit_rqs_slots(sge_assignment_t *a, const char *host, const char *queue,
      int *slots, int *slots_qend, dstring *rule_name, dstring *rue_name, dstring *limit_name)
{
   lListElem *rqs, *rule;
   const char* user = a->user;
   const char* group = a->group;
   const char* project = a->project;
   const char* pe = a->pe_name;

   DENTER(TOP_LAYER, "parallel_check_and_debit_rqs_slots");


   for_each(rqs, a->rqs_list) {


      if (!lGetBool(rqs, RQS_enabled)) {
         continue;
      }
      sge_dstring_clear(rule_name);
      rule = rqs_get_matching_rule(rqs, user, group, project, pe, host, queue, a->acl_list, a->hgrp_list, rule_name);
      if (rule != NULL) {
         lListElem *rql;
         rqs_get_rue_string(rue_name, rule, user, project, host, queue, pe);
         sge_dstring_sprintf(limit_name, "%s=%s", sge_dstring_get_string(rule_name), sge_dstring_get_string(rue_name));
         if ((rql = lGetElemStr(a->limit_list, RQL_name, sge_dstring_get_string(limit_name)))) {
            *slots = MIN(*slots, lGetInt(rql, RQL_slots));
            *slots_qend = MIN(*slots_qend, lGetInt(rql, RQL_slots_qend));
         } else {
            *slots = *slots_qend = 0;
         }
      }

      if (*slots == 0 && *slots_qend == 0) {
         break;
      }
   }


   if (*slots != 0 || *slots_qend != 0) {
      for_each(rqs, a->rqs_list) {


         if (!lGetBool(rqs, RQS_enabled)) {
            continue;
         }
         sge_dstring_clear(rule_name);
         rule = rqs_get_matching_rule(rqs, user, group, project, pe, host, queue, a->acl_list, a->hgrp_list, rule_name);
         if (rule != NULL) {
            lListElem *rql;
            rqs_get_rue_string(rue_name, rule, user, project, host, queue, pe);
            sge_dstring_sprintf(limit_name, "%s=%s", sge_dstring_get_string(rule_name), sge_dstring_get_string(rue_name));
            rql = lGetElemStr(a->limit_list, RQL_name, sge_dstring_get_string(limit_name));
            lSetInt(rql, RQL_slots,      lGetInt(rql, RQL_slots) - *slots);
            lSetInt(rql, RQL_slots_qend, lGetInt(rql, RQL_slots_qend) - *slots_qend);
         }
      }
   }

   DPRINTF(("check_and_debit_rqs_slots(%s@%s) slots: %d slots_qend: %d\n", queue, host, *slots, *slots_qend));

   DRETURN_VOID;
}
