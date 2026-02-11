qmonInitSge(sge_gdi_ctx_class_t **ctx_ref, char *progname, int usage)
{
   int error = 0;
   int endless_loop = 0;
   lList *alp = NULL;
   char* env_var = NULL;
   const char *mastername = NULL;
   u_long32 sge_qmaster_port = 0;
   sge_gdi_ctx_class_t *ctx = NULL;

   DENTER(GUI_LAYER, "qmonInitSge");

   strcpy(SGE_EVENT,"");

   env_var = getenv("SGE_QMON_TEST_QMASTER_ISALIVE");
   if (env_var != NULL) {
      endless_loop = atoi(env_var);
   }
   log_state_set_log_gui(1);
   error = sge_gdi2_setup(ctx_ref, QMON, MAIN_THREAD, &alp);

   if (*ctx_ref != NULL) {
      ctx = *ctx_ref;
      mastername = ctx->get_sge_root(ctx);
      sge_qmaster_port = ctx->get_sge_qmaster_port(ctx);
   }
   if (error != AE_OK) {

      answer_list_output(&alp);

      if ( mastername != NULL) {
         error=ctx->is_alive(ctx);

         if (error == CL_RETVAL_CONNECT_ERROR ||
             error == CL_RETVAL_CONNECTION_NOT_FOUND) {
            SGE_ADD_MSG_ID(sprintf(SGE_EVENT, MSG_GDI_UNABLE_TO_CONNECT_SUS,
                                   prognames[QMASTER],
                                   sge_qmaster_port,
                                   mastername));
         }

         else {
            SGE_ADD_MSG_ID(sprintf(SGE_EVENT, MSG_GDI_CANT_SEND_MSG_TO_PORT_ON_HOST_SUSS,
                                   prognames[QMASTER],
                                   sge_qmaster_port,
                                   mastername,
                                   cl_get_error_text(error)));
         }
         fprintf(stderr, "%s\n", SGE_EVENT);
         if (error != CL_RETVAL_OK) {


            ctx->get_master(ctx, true);
         }
      }
      if (endless_loop == 0) {
         qmonExitFunc(1);
      }
   }

   while (endless_loop > 0) {
      static int nr_of_errors = 0;
      error=ctx->is_alive(ctx);
      printf("checking isalive qmaster (errors=%d, frequency=%d) ...\n", nr_of_errors, endless_loop);
      if (do_qmon_shutdown()) {
         qmonExitFunc(0);
      }
      sleep(endless_loop);
      if (error != CL_RETVAL_OK) {


         ctx->get_master(ctx, true);
      }
   }
   log_state_set_log_gui(0);

   DEXIT;
}
