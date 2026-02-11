waitpid(pid_t pid, int* status, int options)
{
  pid_t ret;

  uint32_t tid = VT_CURRENT_THREAD;


  EXECWRAP_FUNC_INIT("waitpid", pid_t, (pid_t, int*, int));


  VT_SUSPEND_MALLOC_TRACING(tid);

  if( EXECWRAP_DO_TRACE() )
  {
    uint64_t time;


    tid = VT_MY_THREAD;


    time = vt_pform_wtime();


    EXECWRAP_GET_FUNC_ID();


    (void)vt_enter(tid, &time, VT_LIBWRAP_FUNC_ID);


    ret = EXECWRAP_FUNC_CALL((pid, status, options));


    time = vt_pform_wtime();
    vt_exit(tid, &time);
  }
  else
  {

    ret = EXECWRAP_FUNC_CALL((pid, status, options));
  }


  errno = vt_libwrap_get_libc_errno();


  VT_RESUME_MALLOC_TRACING(tid);

  return ret;
}
