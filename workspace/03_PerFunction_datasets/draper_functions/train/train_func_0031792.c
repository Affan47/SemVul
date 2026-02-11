job_handle_subtask(lListElem *job, lListElem *ja_task, lListElem *pe_task,
                              job_handler_t *handler, lList **alpp ) {
   char task_state_string[8];
   u_long32 tstate, tstatus;
   lListElem *ep;
   lList *usage_list;
   lList *scaled_usage_list;

   task_summary_t summary;
   int ret = 0;

   DENTER(TOP_LAYER, "job_handle_subtask");


   if (pe_task == NULL) {
      tstatus = lGetUlong(ja_task, JAT_status);
      usage_list = lGetList(ja_task, JAT_usage_list);
      scaled_usage_list = lGetList(ja_task, JAT_scaled_usage_list);
   } else {
      tstatus = lGetUlong(pe_task, PET_status);
      usage_list = lGetList(pe_task, PET_usage);
      scaled_usage_list = lGetList(pe_task, PET_scaled_usage);
   }

   if (pe_task == NULL) {
      summary.task_id = "";
   } else {
      summary.task_id = lGetString(pe_task, PET_id);
   }


   tstate = lGetUlong(ja_task, JAT_state);
   if (tstatus==JRUNNING) {
      tstate |= JRUNNING;
      tstate &= ~JTRANSFERING;
   } else if (tstatus==JTRANSFERING) {
      tstate |= JTRANSFERING;
      tstate &= ~JRUNNING;
   } else if (tstatus==JFINISHED) {
      tstate |= JEXITING;
      tstate &= ~(JRUNNING|JTRANSFERING);
   }

   if (lGetList(job, JB_jid_predecessor_list) || lGetUlong(ja_task, JAT_hold)) {
      tstate |= JHELD;
   }

   if (lGetUlong(ja_task, JAT_job_restarted)) {
      tstate &= ~JWAITING;
      tstate |= JMIGRATING;
   }


   job_get_state_string(task_state_string, tstate);
   summary.state = task_state_string;

   {
      lListElem *up;


      if (!(up = lGetElemStr(scaled_usage_list, UA_name, USAGE_ATTR_CPU))) {
         summary.has_cpu_usage = false;
      } else {
         summary.has_cpu_usage = true;
         summary.cpu_usage = lGetDouble(up, UA_value);
      }


      if (!(up = lGetElemStr(scaled_usage_list, UA_name, USAGE_ATTR_MEM))) {
         summary.has_mem_usage = false;
      } else {
         summary.has_mem_usage = true;
         summary.mem_usage = lGetDouble(up, UA_value);
      }


      if (!(up = lGetElemStr(scaled_usage_list, UA_name, USAGE_ATTR_IO))) {
         summary.has_io_usage = false;
      } else {
         summary.has_io_usage = true;
         summary.io_usage = lGetDouble(up, UA_value);
      }
   }

   if (tstatus==JFINISHED) {
      ep=lGetElemStr(usage_list, UA_name, "exit_status");
      if (ep) {
         summary.has_exit_status = true;
         summary.exit_status = (int)lGetDouble(ep, UA_value);
      } else {
         summary.has_exit_status = false;
      }
   } else {
      summary.has_exit_status = false;
   }

   ret = handler->report_sub_task(handler, &summary, alpp);

   DRETURN(ret);
}
