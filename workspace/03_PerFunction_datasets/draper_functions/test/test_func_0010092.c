set_flush(void)
{
   DENTER(TOP_LAYER, "set_flush");

   sge_mutex_lock("event_master_cond_mutex", SGE_FUNC, __LINE__, &Event_Master_Control.cond_mutex);
   if (!Event_Master_Control.delivery_signaled) {
      Event_Master_Control.delivery_signaled = true;
      pthread_cond_signal(&Event_Master_Control.cond_var);
   }
   sge_mutex_unlock("event_master_cond_mutex", SGE_FUNC, __LINE__, &Event_Master_Control.cond_mutex);

   DRETURN_VOID;
}
