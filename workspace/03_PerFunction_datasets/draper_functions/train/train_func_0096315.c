TestMainLoop()
{
  command *Command;
  char    *Scan;

  TestCommandViewSystem( (char *)0 );

  TestExit = 0;

  do
  {
    fprintf( stdout, "\ncommand > " );

    if ( ! fgets( TestBuffer, BDD_TEST_BUFFER_SIZE, stdin ) )
    {
      fprintf( stderr, "Interrupt by user\n" );

      return( 0 );
    }

    Scan = strchr( TestBuffer, '\n' );

    if ( Scan != (char *)0 )
    {
      *Scan = '\0';
    }

    Scan = strchr( TestBuffer, ' '  );

    if ( Scan != (char *)0 )
    {
      *Scan = '\0'; Scan = Scan + 1;
    }

    Command = TestGetCommand( TestBuffer );

    if ( Command != (command *)0 )
    {
      (*Command->FUNCTION)( Scan );
    }
    else
    {
      fprintf( stderr, "syntax error\n" );
    }
  }
  while ( ( TestExit   == 0 ) &&
          ( TestLogout == 0 ) );

  return( 1 );
}
