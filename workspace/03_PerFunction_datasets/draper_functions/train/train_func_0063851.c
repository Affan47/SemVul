VT_User_update_counter__()
{
  uint64_t time;

  VT_INIT;

  VT_SUSPEND_MALLOC_TRACING(VT_CURRENT_THREAD);

  time = vt_pform_wtime();
  vt_update_counter(VT_CURRENT_THREAD, &time);

  VT_RESUME_MALLOC_TRACING(VT_CURRENT_THREAD);
}
