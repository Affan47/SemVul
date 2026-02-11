sconf_eval_set_monitoring(lList *param_list, lList **answer_list, const char* param){
   bool ret = true;
   lListElem *elem = NULL;
   const char mon_true[] = "MONITOR=TRUE", mon_one[] = "MONITOR=1";
   const char mon_false[] = "MONITOR=FALSE", mon_zero[] = "MONITOR=0";
   bool do_monitoring = false;

   DENTER(TOP_LAYER, "sconf_eval_set_monitoring");

   if (!strncasecmp(param, mon_one, sizeof(mon_one)-1) ||
       !strncasecmp(param, mon_true, sizeof(mon_true)-1) ) {
      do_monitoring = true;
      elem = lCreateElem(PARA_Type);
      lSetString(elem, PARA_name, "monitor");
      lSetString(elem, PARA_value, "true");
   }
   else if (!strncasecmp(param, mon_zero, sizeof(mon_zero)-1) ||
            !strncasecmp(param, mon_false, sizeof(mon_false)-1) ) {
      elem = lCreateElem(PARA_Type);
      lSetString(elem, PARA_name, "monitor");
      lSetString(elem, PARA_value, "false");
   }
   else {
      SGE_ADD_MSG_ID(sprintf(SGE_EVENT, MSG_INVALID_PARAM_SETTING_S, param));
      answer_list_add(answer_list, SGE_EVENT, STATUS_ESYNTAX, ANSWER_QUALITY_ERROR);
      ret = false;
   }
   if (elem){
      lAppendElem(param_list, elem);
   }

   current_serf_do_monitoring = do_monitoring;

   DRETURN(ret);
}
