handle_spin_trylock ()
{
  FUNC_NAME;
  int result = GET_PARAM(CUR_EV, 2);
  if(result) {
    DECLARE_THREAD_ID_STR(thread_id, CUR_INDEX, CUR_THREAD_ID);
    DECLARE_CUR_PROCESS(p_process);

    app_ptr lock_ptr = (app_ptr) GET_PARAM(CUR_EV, 1);
    struct pthread_lock_info_t *lock_info = NULL;
    GET_LOCK_INFO(lock_info, p_process, lock_ptr, SPINLOCK);
    record_lock_acquired(lock_info);

    PTHREAD_CHANGE() pushState(CURRENT, "ST_Thread", thread_id, "STV_Critical_spin");
  }
}
