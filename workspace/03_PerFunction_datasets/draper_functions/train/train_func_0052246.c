initCommand( void )
{
  CommandList = new_ctnr();
  sigemptyset( &SignalSet );
  sigaddset( &SignalSet, SIGALRM );

  registerCommand( "monitors", printMonitors );


  if ( RunAsDaemon == 0 )
    registerCommand( "quit", exQuit );
}
