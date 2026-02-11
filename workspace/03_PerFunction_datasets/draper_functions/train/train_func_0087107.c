TestCommandAddElement( String )

  char *String;
{
  authelem *AutElement;
  char     *Scan;

  if ( TestMode2 ) return;

  if ( String != (char *)0 )
  {
    Scan = strchr( String, ' ' );

    if ( Scan != (char *)0 )
    {
      *Scan = '\0';
    }

    String = namealloc( String );
    fprintf( stdout, "--> addelem %s\n", String );

    AutElement = addauthelem( TestHashTable, String, TestIndex++ );
    viewauthelem( AutElement );
  }
}
