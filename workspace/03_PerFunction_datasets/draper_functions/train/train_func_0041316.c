read_pref_work(
lList **alpp,
lList **clpp,
int fields[],
lListElem *ep,
int spool,
int flag,
int *tag,
int parsing_type
) {
   static int intprt_as_cplx_entry[] = {
      CE_name,
      CE_stringval,
      0
   };

   DENTER(TOP_LAYER, "read_pref_work");


   if (!set_conf_deflist(alpp, clpp, fields, "job_filter_resources", ep,
                      PREF_job_filter_resources,
                        CE_Type, intprt_as_cplx_entry)) {
      DEXIT;
      return -1;
   }


   if (!set_conf_list(alpp, clpp, fields, "job_filter_owners", ep,
                      PREF_job_filter_owners, ST_Type, ST_name)) {
      DEXIT;
      return -1;
   }


   if (!set_conf_list(alpp, clpp, fields, "job_filter_fields", ep,
                      PREF_job_filter_fields, ST_Type, ST_name)) {
      DEXIT;
      return -1;
   }


   set_conf_bool(NULL, clpp, fields, "job_filter_compact", ep,
                 PREF_job_filter_compact);


   if (!set_conf_deflist(alpp, clpp, fields, "queue_filter_resources", ep,
                      PREF_queue_filter_resources,
                      CE_Type, intprt_as_cplx_entry)) {
      DEXIT;
      return -1;
   }


   if (!set_conf_list(alpp, clpp, fields, "queue_filter_pe", ep,
                      PREF_queue_filter_pe, ST_Type, ST_name)) {
      DEXIT;
      return -1;
   }


   if (!set_conf_list(alpp, clpp, fields, "queue_filter_user", ep,
                      PREF_queue_filter_user, ST_Type, ST_name)) {
      DEXIT;
      return -1;
   }


   if (!set_conf_list(alpp, clpp, fields, "queue_filter_q", ep,
                      PREF_queue_filter_q, QR_Type, QR_name)) {
      DEXIT;
      return -1;
   }


   if (!set_conf_string(alpp, clpp, fields, "queue_filter_state", ep,
                 PREF_queue_filter_state)) {
      DEXIT;
      return -1;
   }


   if (!set_conf_list(alpp, clpp, fields, "ar_filter_fields", ep,
                      PREF_ar_filter_fields, ST_Type, ST_name)) {
      DEXIT;
      return -1;
   }

   DEXIT;
   return 0;
}
