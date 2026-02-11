PrintStatus(
lListElem *ep,
lListElem *jat,
lList *eleml,
int nm
) {
   lList *ql = NULL;
   int n;
   char buf[128] = "";
   String str;
   u_long32 tstate = 0;
   u_long32 tstatus = 0;

   DENTER(GUI_LAYER, "PrintStatus");

   if (eleml && !jat) {
      lListElem *first_elem = lFirst(eleml);

      if (object_has_type(first_elem, JAT_Type)) {
         jat = lFirst(eleml);
      } else if (object_has_type(first_elem, RN_Type)) {
         u_long32 task_id = range_list_get_first_id(eleml, NULL);

         jat = job_get_ja_task_template(ep, task_id);
      }
   }

   if (jat) {
      ql = lGetList(jat, JAT_granted_destin_identifier_list);
      n = lGetNumberOfElem(ql);
   }
   else {
      n = 0;
   }

   if (job_is_zombie_job(ep)) {
      str = XtNewString("NA");
   } else {

      tstatus = lGetUlong(jat, JAT_status);
      tstate = lGetUlong(jat, JAT_state);

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


      if (n>0) {
         if ((tstate & JSUSPENDED_ON_SUBORDINATE) ||
             (tstate & JSUSPENDED_ON_SLOTWISE_SUBORDINATE)) {
            tstate &= ~JRUNNING;
            lSetUlong(jat, JAT_state, tstate);
         }
      }

      if (lGetList(ep, JB_jid_predecessor_list) || lGetUlong(jat, JAT_hold)) {
         tstate |= JHELD;
      }

      if (lGetUlong(jat, JAT_job_restarted)) {
         tstate &= ~JWAITING;
         tstate |= JMIGRATING;
      }


      job_get_state_string(buf, tstate);

      str = XtNewString(buf);
   }

   DEXIT;
   return str;
}
