sge_thread_notify_all_waiting(void)
{
   DENTER(THREAD_LAYER, "sge_thread_notify_all_waiting");

   sge_mutex_lock(THREAD_CONTROL_MUTEX, SGE_FUNC, __LINE__, &Thread_Control.mutex);

   Thread_Control.shutdown_started = true;
   pthread_cond_broadcast(&Thread_Control.cond_var);

   sge_mutex_unlock(THREAD_CONTROL_MUTEX, SGE_FUNC, __LINE__, &Thread_Control.mutex);

   DRETURN_VOID;
}
