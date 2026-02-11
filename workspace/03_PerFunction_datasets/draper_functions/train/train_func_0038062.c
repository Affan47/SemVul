main(int argc, char **argv) {
   int ret = 0;
   lList *pcmdline = NULL;
   lList *answer_list = NULL;
   sge_gdi_ctx_class_t *ctx = NULL;
   qrstat_env_t qrstat_env;

   DENTER_MAIN(TOP_LAYER, "qrsub");


   sge_setup_sig_handlers(QRSTAT);

   log_state_set_log_gui(1);

   if (sge_gdi2_setup(&ctx, QRSTAT, MAIN_THREAD, &answer_list) != AE_OK) {
      answer_list_output(&answer_list);
      goto error_exit;
   }

   qrstat_filter_init(&qrstat_env);
   qrstat_filter_set_ctx(&qrstat_env, ctx);


   {
      dstring file = DSTRING_INIT;
      const char *user = ctx->get_username(ctx);
      const char *cell_root = ctx->get_cell_root(ctx);


      get_root_file_path(&file, cell_root, SGE_COMMON_DEF_QRSTAT_FILE);
      if (sge_parse_from_file_qrstat(sge_dstring_get_string(&file), &pcmdline, &answer_list) == true) {

         if (get_user_home_file_path(&file, SGE_HOME_DEF_QRSTAT_FILE, user, &answer_list)) {
            sge_parse_from_file_qrstat(sge_dstring_get_string(&file), &pcmdline, &answer_list);
         }
      }
      sge_dstring_free(&file);

      if (answer_list) {
         answer_list_output(&answer_list);
         lFreeList(&pcmdline);
         sge_prof_cleanup();
         SGE_EXIT((void**)&ctx, 1);
      }
   }

   answer_list = cull_parse_cmdline(QRSTAT, argv+1, environ, &pcmdline, FLG_USE_PSEUDOS);
   if (answer_list != NULL) {
      answer_list_output(&answer_list);
      lFreeList(&pcmdline);
      goto error_exit;
   }


   if (!sge_parse_qrstat(ctx, &answer_list, &qrstat_env, &pcmdline)) {
      answer_list_output(&answer_list);
      lFreeList(&pcmdline);
      goto error_exit;
   }


   {
      answer_list = ctx->gdi(ctx, SGE_AR_LIST, SGE_GDI_GET, &qrstat_env.ar_list,
                     qrstat_env.where_AR_Type, qrstat_env.what_AR_Type);

      if (answer_list_has_error(&answer_list)) {
         answer_list_output(&answer_list);
         goto error_exit;
      }
   }


   {
      qrstat_report_handler_t *handler = NULL;

      if (qrstat_env.is_xml) {
         handler = qrstat_create_report_handler_xml(&qrstat_env, &answer_list);
      } else {
         handler = qrstat_create_report_handler_stdout(&qrstat_env, &answer_list);
      }
      if (!qrstat_print(&answer_list, handler, &qrstat_env)) {
         ret = 1;
      }
      if (qrstat_env.is_xml) {
         qrstat_destroy_report_handler_xml(&handler, &answer_list);
      } else {
         qrstat_destroy_report_handler_stdout(&handler, &answer_list);
      }
   }

   sge_gdi2_shutdown((void**)&ctx);
   sge_prof_cleanup();
   DRETURN(ret);

error_exit:
   sge_gdi2_shutdown((void**)&ctx);
   sge_prof_cleanup();
   SGE_EXIT((void**)&ctx, 1);
   DRETURN(1);
}
