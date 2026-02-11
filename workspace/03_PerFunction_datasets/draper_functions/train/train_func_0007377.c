_initJassertOutputDevices()
{
  pthread_mutex_t newLock = PTHREAD_MUTEX_INITIALIZER;
  logLock = newLock;

  const char* errpath = getenv ( "JALIB_STDERR_PATH" );

#ifdef DEBUG
  if ( errpath != NULL && theLogFileFd == -1 ) {
    JASSERT_SET_LOGFILE ( jalib::XToString(getenv("DMTCP_TMPDIR"))
                          + "/jassertlog." + jalib::XToString ( getpid() ) );
  }
#endif

  if ( errpath != NULL )
    errConsoleFd = _open_log_safe ( errpath, jalib::stderrFd );
  else
    errConsoleFd = dup2 ( fileno ( stderr ), jalib::stderrFd );

  if( errConsoleFd == -1 ) {
    jwrite ( fileno (stderr ), "dmtcp: cannot open output channel for error logging\n");
    return false;
  }
  return true;
}
