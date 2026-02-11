daytime_range(lListElem **tmr) {
   lListElem *t1 = NULL, *t2 = NULL;

   DENTER(TOP_LAYER, "daytime_range");

   if (daytime(&t1)) {
      goto ERROR;
   }
   if (scan(NULL, NULL)!=MINUS) {
      sprintf(parse_error, MSG_PARSE_MISSINGDASHINDAYTIMERANGE);
      goto ERROR;
   }
   eat_token();
   if (daytime(&t2)) {
      goto ERROR;
   }
   if (!tm_daytime_cmp(t1, t2)) {
      sprintf(parse_error, MSG_PARSE_RANGEBEGISEQUALTOEND);
      goto ERROR;
   }

   if (tmr) {
      lList *tmlp;

      *tmr = lCreateElem(TMR_Type);

      tmlp = lCreateList("tm_list", TM_Type);
      lAppendElem(tmlp, t1);
      t1 = NULL;
      lSetList(*tmr, TMR_begin, tmlp);

      tmlp = lCreateList("tm_list", TM_Type);
      lAppendElem(tmlp, t2);
      t2 = NULL;
      lSetList(*tmr, TMR_end, tmlp);
   }

   lFreeElem(&t1);
   lFreeElem(&t2);

   DRETURN(0);

ERROR:
   lFreeElem(&t1);
   lFreeElem(&t2);
   DRETURN(-1);
}
