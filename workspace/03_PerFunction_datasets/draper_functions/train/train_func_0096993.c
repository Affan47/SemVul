resetHandlers()
{
  if( !Private::handlerSet )
      return;
  Private::handlerSet = false;

#ifdef Q_OS_UNIX
  sigset_t mask, omask;
  sigemptyset( &mask );
  sigaddset( &mask, SIGCHLD );
  sigprocmask( SIG_BLOCK, &mask, &omask );

  struct sigaction act;
  sigaction( SIGCHLD, &Private::oldChildHandlerData, &act );
  if (act.sa_handler != theReaper) {
     sigaction( SIGCHLD, &act, 0 );
     Private::handlerSet = true;
  }

  sigprocmask( SIG_SETMASK, &omask, 0 );
#else

#endif

}
