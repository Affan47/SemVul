XsbGetFirstWord( Buffer, IsKeyword, Hash )

  char *Buffer;
  char  IsKeyword;
  char  Hash;
{
  char   *String;
  char   *Text;
  int     Index;

  autbegin();

  if ( String = (char *)strtok( Buffer, XSB_SEPARATORS_STRING ))
  {
    if ( Hash )
    {
      String = namealloc( String );
    }
    else
    {
      Text = autallocblock( strlen( String ) + 1 );
      strcpy( Text, String );
      String = Text;

      for ( Index = 0; Text[ Index ]; Index++ )
      {
        if ( Text[ Index ] == '_' ) Text[ Index ] = ' ';
      }
    }

    if ( ( IsKeyword ) && XsbCheckKeyword( String ) )
    {
      XsbError( UNEXPECTED_LINE, String, XsbCurrentLine );
    }
  }

  autend();
  return( String );
}
