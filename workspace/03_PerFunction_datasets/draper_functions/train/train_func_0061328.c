reset_oom_protect() {
   if( oom_pipe <= 0 )
      return;
   struct sigaction act, oldact;
   act.sa_handler = oom_protect_sighandler;
   act.sa_flags = 0;
   sigemptyset( &act.sa_mask );
   sigaction( SIGUSR1, &act, &oldact );
   sigset_t sigs, oldsigs;
   sigemptyset( &sigs );
   sigaddset( &sigs, SIGUSR1 );
   sigprocmask( SIG_BLOCK, &sigs, &oldsigs );
   pid_t pid = getpid();
   if( write( oom_pipe, &pid, sizeof( pid_t )) > 0 ) {
      sigsuspend( &oldsigs );
   } else {
#ifndef NDEBUG
      fprintf( stderr, "Failed to reset OOM protection: %d\n", pid );
#endif
   }
   sigprocmask( SIG_SETMASK, &oldsigs, NULL );
   sigaction( SIGUSR1, &oldact, NULL );
   close( oom_pipe );
   oom_pipe = -1;
}
