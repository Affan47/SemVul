main(int argc, char **argv)
{
   lList *pcmdline = NULL;
   lList *host_list = NULL;
   lList *resource_match_list = NULL;
   lList *user_list = NULL;
   lList *pe_list = NULL;
   lList *project_list = NULL;
   lList *cqueue_list = NULL;
   lList *alp = NULL;
   report_handler_t *report_handler = NULL;
   bool qquota_result = true;
   sge_gdi_ctx_class_t *ctx = NULL;

   DENTER_MAIN(TOP_LAYER, "qquota");

   log_state_set_log_gui(true);

   if (sge_gdi2_setup(&ctx, QQUOTA, MAIN_THREAD, &alp) != AE_OK) {
      answer_list_output(&alp);
      sge_prof_cleanup();
      SGE_EXIT((void**)&ctx, 1);
   }

   sge_setup_sig_handlers(QQUOTA);


   {
      dstring file = DSTRING_INIT;
      const char *user = ctx->get_username(ctx);
      const char *cell_root = ctx->get_cell_root(ctx);


      get_root_file_path(&file, cell_root, SGE_COMMON_DEF_QQUOTA_FILE);
      if (sge_parse_from_file_qquota(sge_dstring_get_string(&file), &pcmdline, &alp) == true) {

         if (get_user_home_file_path(&file, SGE_HOME_DEF_QQUOTA_FILE, user, &alp)) {
            sge_parse_from_file_qquota(sge_dstring_get_string(&file), &pcmdline, &alp);
         }
      }
      sge_dstring_free(&file);

      if (alp) {
         answer_list_output(&alp);
         lFreeList(&pcmdline);
         sge_prof_cleanup();
         SGE_EXIT((void**)&ctx, 1);
      }
   }
   if (sge_parse_cmdline_qquota(argv, &pcmdline, &alp) == false) {
      answer_list_output(&alp);
      lFreeList(&pcmdline);
      sge_prof_cleanup();
      SGE_EXIT((void**)&ctx, 1);
   }


   if (sge_parse_qquota(&pcmdline,
            &host_list,
            &resource_match_list,
            &user_list,
            &pe_list,
            &project_list,
            &cqueue_list,
            &report_handler,
            &alp) == false) {


      answer_list_output(&alp);
      lFreeList(&pcmdline);
      sge_prof_cleanup();
      SGE_EXIT((void**)&ctx, 1);
   }

   qquota_result = qquota_output(ctx, host_list, resource_match_list, user_list, pe_list, project_list, cqueue_list, &alp, report_handler);

   if (report_handler != NULL ) {
      report_handler->destroy(&report_handler, &alp);
   }

   if (qquota_result == false) {
      answer_list_output(&alp);
      sge_prof_cleanup();
      SGE_EXIT((void**)&ctx, 1);
   }

   sge_prof_cleanup();
   SGE_EXIT((void**)&ctx, 0);
   DEXIT;
   return 0;
}
