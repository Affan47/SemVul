sge_listener_initialize(sge_gdi_ctx_class_t *ctx)
{
   const u_long32 max_initial_listener_threads = ctx->get_listener_thread_count(ctx);
   cl_thread_settings_t* dummy_thread_p = NULL;
   u_long32 i;

   DENTER(TOP_LAYER, "sge_listener_initialize");

   INFO((SGE_EVENT, MSG_QMASTER_THREADCOUNT_US, sge_u32c(max_initial_listener_threads), threadnames[LISTENER_THREAD]));
   cl_thread_list_setup(&(Main_Control.listener_thread_pool), "thread pool");
   for (i = 0; i < max_initial_listener_threads; i++) {
      dstring thread_name = DSTRING_INIT;

      sge_dstring_sprintf(&thread_name, "%s%03d", threadnames[LISTENER_THREAD], i);
      cl_thread_list_create_thread(Main_Control.listener_thread_pool, &dummy_thread_p,
                                   cl_com_get_log_list(), sge_dstring_get_string(&thread_name), i,
                                   sge_listener_main, NULL, NULL, CL_TT_LISTENER);
      sge_dstring_free(&thread_name);
   }
   DRETURN_VOID;
}
