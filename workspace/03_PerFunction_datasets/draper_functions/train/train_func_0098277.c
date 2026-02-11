execlp(const char* file, const char* arg, ...)
{
  int ret;

  uint32_t tid = VT_MASTER_THREAD;

  va_list ap;
  const char* argv[EXECWRAP_EXECL_MAX_ARGS];


  EXECWRAP_FUNC_INIT("execlp", int, (const char*, const char*, ...));


  VT_SUSPEND_MALLOC_TRACING(tid);


  if( EXECWRAP_DO_TRACE() )
  {
    uint64_t time;


    time = vt_pform_wtime();


    EXECWRAP_GET_FUNC_ID();


    (void)vt_enter(tid, &time, VT_LIBWRAP_FUNC_ID);
  }


  va_start(ap, arg);
  execwrap_execl_valist_to_argv(ap, arg, argv);
  va_end(ap);


  VT_SUSPEND_EXEC_TRACING(tid);


  ret = execvp(file, (char* const*)argv);


  return ret;
}
