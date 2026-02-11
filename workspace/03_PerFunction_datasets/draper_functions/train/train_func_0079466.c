rqs_parse_filter_from_string(lListElem **filter, const char* buffer, lList **alp) {
   lListElem *tmp_filter = NULL;
   lListElem *scope = NULL;
   lList *lp = NULL;
   lList *scope_list = NULL;
   lList *xscope_list = NULL;
   char delims[] = "\t \v\r,{}";

   DENTER(TOP_LAYER, "rqs_parse_filter_from_string");

   if (buffer == NULL) {
     DRETURN(false);
   }

   tmp_filter = lCreateElem(RQRF_Type);

   if ( buffer[0] == '{' ) {

      lSetBool(tmp_filter, RQRF_expand, true);
      if (buffer[strlen(buffer)-1] != '}') {
         ERROR((SGE_EVENT, MSG_RESOURCEQUOTA_NOVALIDEXPANDEDLIST));
         answer_list_add(alp, SGE_EVENT, STATUS_ESYNTAX, ANSWER_QUALITY_ERROR);
         DRETURN(false);
      }
   } else {
      lSetBool(tmp_filter, RQRF_expand, false);
   }

   lString2List(buffer, &lp, ST_Type, ST_name, delims);

   for_each(scope, lp) {
      const char *name = lGetString(scope, ST_name);
      if ( name[0] == '!' ) {
         lAddElemStr(&xscope_list, ST_name, name+1, ST_Type);
      } else {
         lAddElemStr(&scope_list, ST_name, name, ST_Type);
      }
   }

   lFreeList(&lp);

   lSetList(tmp_filter, RQRF_scope, scope_list);
   lSetList(tmp_filter, RQRF_xscope, xscope_list);

   *filter = tmp_filter;

   DRETURN(true);
}
