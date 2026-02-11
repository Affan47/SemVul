init_framework(const char *method, const char *shlib,
                          const char *libargs, bool check_context)
{
   int ret = EXIT_FAILURE;

   lListElem *spooling_context = NULL;
   lList *answer_list = NULL;

   DENTER(TOP_LAYER, "init_framework");

#ifdef HP1164
   sge_set_admin_username("none", NULL);
#endif

   spooling_context = spool_create_dynamic_context(&answer_list, method, shlib,
                                                   libargs);
   answer_list_output(&answer_list);
   if (spooling_context == NULL) {
      CRITICAL((SGE_EVENT, MSG_SPOOLDEFAULTS_CANNOTCREATECONTEXT));
   } else {
      spool_set_default_context(spooling_context);


      if (!spool_startup_context(&answer_list, spooling_context,
                                 check_context)) {
         CRITICAL((SGE_EVENT, MSG_SPOOLDEFAULTS_CANNOTSTARTUPCONTEXT));
      } else {
         ret = EXIT_SUCCESS;
      }
      answer_list_output(&answer_list);
   }

   DEXIT;
   return ret;
}
