rc_add_job_utilization(lListElem *jep, u_long32 task_id, const char *type,
   lListElem *ep, lList *centry_list, int slots, int config_nm, int actual_nm,
   const char *obj_name, u_long32 start_time, u_long32 duration, u_long32 tag,
   bool for_job_scheduling, bool is_master_task)
{
   lListElem *cr, *cr_config, *dcep;
   int mods = 0;

   DENTER(TOP_LAYER, "rc_add_job_utilization");

   if (!ep) {
      ERROR((SGE_EVENT, "rc_add_job_utilization NULL object "
            "(job "sge_u32" obj %s type %s) slots %d ep %p\n",
            lGetUlong(jep, JB_job_number), obj_name, type, slots, ep));
      DRETURN(0);
   }

   if (!slots) {
      ERROR((SGE_EVENT, "rc_add_job_utilization 0 slot amount "
            "(job "sge_u32" obj %s type %s) slots %d ep %p\n",
            lGetUlong(jep, JB_job_number), obj_name, type, slots, ep));
      DRETURN(0);
   }

   for_each(cr_config, lGetList(ep, config_nm)) {
      u_long32 consumable;
      const char *name = lGetString(cr_config, CE_name);
      double dval = 0.0;
      int debit_slots = slots;


      if (!(dcep = centry_list_locate(centry_list, name))) {
         ERROR((SGE_EVENT, MSG_ATTRIB_MISSINGATTRIBUTEXINCOMPLEXES_S , name));
         DRETURN(-1);
      }

      consumable = lGetUlong(dcep, CE_consumable);
      if (consumable == CONSUMABLE_NO) {

         continue;
      }

      if (consumable == CONSUMABLE_JOB) {
         if (!is_master_task) {

            continue;
         }

         if (slots > 0) {
            debit_slots = 1;
         } else if (slots < 0) {
            debit_slots = -1;
         }
      }


      if (!(cr = lGetSubStr(ep, RUE_name, name, actual_nm))) {
         cr = lAddSubStr(ep, RUE_name, name, actual_nm, RUE_Type);

      }

      if (job_get_contribution(jep, NULL, name, &dval, dcep) && dval != 0.0) {

         utilization_add(cr, start_time, duration, debit_slots * dval,
            lGetUlong(jep, JB_job_number), task_id, tag, obj_name, type, for_job_scheduling, false);
         mods++;
      } else if (lGetUlong(dcep, CE_relop) == CMPLXEXCL_OP) {
         dval = 1.0;

         utilization_add(cr, start_time, duration, debit_slots * dval,
            lGetUlong(jep, JB_job_number), task_id, tag, obj_name, type, for_job_scheduling, true);
         mods++;
      }

   }

   DRETURN(mods);
}
