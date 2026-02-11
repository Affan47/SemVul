attr_mod_time_str(lList **alpp, lListElem *qep, lListElem *new_ep, int nm, char *attr_name, int enable_infinity)
{
   DENTER(TOP_LAYER, "attr_mod_time_str");


   if (lGetPosViaElem(qep, nm, SGE_NO_ABORT)>=0) {
      const char *str;

      str = lGetString(qep, nm);
      DPRINTF(("got new %s\n", attr_name));

      if (str != NULL ) {

         if ((strcasecmp(str, "infinity") == 0) && (enable_infinity == 0)) {
              DPRINTF(("ERROR! Infinity value for \"%s\"\n",attr_name));
              SGE_ADD_MSG_ID(sprintf(SGE_EVENT, MSG_GDI_SIG_DIGIT_SS, attr_name, str));
              answer_list_add(alpp, SGE_EVENT, STATUS_ESYNTAX, ANSWER_QUALITY_ERROR);
              DEXIT;
              return STATUS_ESYNTAX;
         }
      }

      if(!parse_ulong_val(NULL, NULL, TYPE_TIM, str, NULL, 0)) {
         SGE_ADD_MSG_ID(sprintf(SGE_EVENT, MSG_GDI_TYPE_TIME_SS, attr_name, str?str:"(null)"));
         answer_list_add(alpp, SGE_EVENT, STATUS_ESYNTAX, ANSWER_QUALITY_ERROR);
         DEXIT;
         return STATUS_ESYNTAX;
      }

      lSetString(new_ep, nm, str);
   }

   DEXIT;
   return 0;
}
