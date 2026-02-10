init_framework(sge_gdi_ctx_class_t *ctx, bdb_info *info)
{
   int ret = EXIT_FAILURE;

   lList *answer_list = NULL;
   lListElem *spooling_context = NULL;
   const char *spooling_method = ctx->get_spooling_method(ctx);
   const char *spooling_lib = ctx->get_spooling_lib(ctx);
   const char *spooling_params = ctx->get_spooling_params(ctx);

   DENTER(TOP_LAYER, "init_framework");

#ifdef HP1164
   sge_set_admin_username("none", NULL);
#endif


   spooling_context = spool_create_dynamic_context(&answer_list,
                                                   spooling_method,
                                                   spooling_lib,
                                                   spooling_params);
   answer_list_output(&answer_list);
   if (!strcmp(bootstrap_get_spooling_method(),"classic")) {
      CRITICAL((SGE_EVENT, MSG_SPOOLDEFAULTS_CANTHANDLECLASSICSPOOLING));
   } else if (spooling_context == NULL) {
      CRITICAL((SGE_EVENT, MSG_SPOOLDEFAULTS_CANNOTCREATECONTEXT));
   } else {
      spool_set_default_context(spooling_context);
      spool_set_option(&answer_list, spooling_context, "recover=false");
      answer_list_output(&answer_list);


      if (!spool_startup_context(&answer_list, spooling_context, true)) {
         CRITICAL((SGE_EVENT, MSG_SPOOLDEFAULTS_CANNOTSTARTUPCONTEXT));
      } else {


         lListElem *type = spool_context_search_type(spooling_context,
                                                     SGE_TYPE_JOB);
         lListElem *rule = spool_type_search_default_rule(type);
         *info = (bdb_info)lGetRef(rule, SPR_clientdata);
         ret = EXIT_SUCCESS;
      }
      answer_list_output(&answer_list);
   }

   DRETURN(ret);
}
