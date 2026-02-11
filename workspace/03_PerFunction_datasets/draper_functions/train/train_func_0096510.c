TestCommandViewElement2( String )

  char *String;
{
  auth2elem *AutElement;
  char      *Scan;

  if ( ! TestMode2 ) return;

  if ( String != (char *)0 )
  {
    Scan = strchr( String, ' ' );

    if ( Scan != (char *)0 )
    {
      *Scan = '\0';
    }

    String = namealloc( String   );
    Scan   = namealloc( Scan + 1 );
    fprintf( stdout, "--> viewelem2 %s %s\n", String, Scan );

    AutElement = searchauth2elem( TestHashTable2, String, Scan );

    if ( AutElement != (auth2elem *)0 )
    {
      viewauth2elem( AutElement );
    }
    else
    {
      fprintf( stderr, "Element %s %s doesn't exist\n", String, Scan );
    }
  }
  else
  {
    viewauth2table( TestHashTable2, viewauth2elem );
  }
}
