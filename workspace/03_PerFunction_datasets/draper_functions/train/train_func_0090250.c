VT_User_end__(const char* name)
{
  uint64_t time;

  (void)name;

  VT_SUSPEND_MALLOC_TRACING(VT_CURRENT_THREAD);


  time = vt_pform_wtime();
  vt_exit(VT_CURRENT_THREAD, &time);

  VT_RESUME_MALLOC_TRACING(VT_CURRENT_THREAD);
}
