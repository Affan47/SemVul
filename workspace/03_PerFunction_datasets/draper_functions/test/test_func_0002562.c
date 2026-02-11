lGetElemHostFirst(const lList *lp, int nm, const char *str,
                             const void **iterator) {

   int pos;
   int data_type;
   lListElem *ep = NULL;
   const lDescr *listDescriptor = NULL;
   char uhost[CL_MAXHOSTLEN+1];
   char cmphost[CL_MAXHOSTLEN+1];
   const char *s = NULL;

   DENTER(TOP_LAYER, "lGetElemHostFirst");


   if ( (str == NULL) || (lp == NULL) ) {
      DPRINTF(("error: NULL ptr passed to lGetElemHostFirst\n"));
      DEXIT;
      return NULL;
   }


   listDescriptor = lGetListDescr(lp);
   pos = lGetPosInDescr(listDescriptor, nm);
   data_type = lGetPosType(listDescriptor, pos);
   if ( (pos < 0) || (data_type != lHostT) ) {
      if (data_type != lHostT) {
         DPRINTF((":::::::::::::::: lGetElemHostFirst - data type is not lHostT !!! :::::::\n"));
      }
      CRITICAL((SGE_EVENT, MSG_CULL_GETELEMHOSTERRORXRUNTIMETYPE_S , lNm2Str(nm)));
      DEXIT;
      return NULL;
   }

   *iterator = NULL;
   if (lp->descr[pos].ht != NULL) {

      char host_key[CL_MAXHOSTLEN+1];
      sge_hostcpy(host_key,str);
      sge_strtoupper(host_key,CL_MAXHOSTLEN);
      ep = cull_hash_first(lp->descr[pos].ht, host_key,
                           mt_is_unique(lp->descr[pos].mt), iterator);
      DEXIT;
      return ep;
   } else {


      sge_hostcpy(uhost, str);


      for_each(ep, lp) {
         s = lGetPosHost(ep, pos);
         if (s != NULL) {
            sge_hostcpy(cmphost, s);
            if ( !SGE_STRCASECMP(cmphost, uhost) ) {
               *iterator = ep;
               DEXIT;
               return ep;
            }
         }
      }
   }

   DEXIT;
   return NULL;
}
