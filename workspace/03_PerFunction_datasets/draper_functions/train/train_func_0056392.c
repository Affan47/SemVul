sge_signaler_terminate(void)
{
   cl_thread_settings_t* thread = NULL;
   DENTER(TOP_LAYER, "sge_signaler_terminate");

   thread = cl_thread_list_get_first_thread(Main_Control.signal_thread_pool);
   if (thread != NULL) {
      DPRINTF(("getting canceled\n"));
      cl_thread_list_delete_thread(Main_Control.signal_thread_pool, thread);
   }
   DRETURN_VOID;
}
