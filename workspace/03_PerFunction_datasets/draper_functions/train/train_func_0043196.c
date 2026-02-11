LynxGetVectorName( Name )

  char *Name;
{
  char *ScanName;

  ScanName = strrchr( Name, ']' );

  if ( ScanName != (char *)0 )
  {
    strcpy( LynxNameBuffer, Name );

    Name = strrchr( LynxNameBuffer, ']' );
    if ( Name != (char *)0 ) *Name = '\0';

    Name = strrchr( LynxNameBuffer, '[' );
    if ( Name != (char *)0 ) *Name = ' ';

    Name = namealloc( LynxNameBuffer );
  }

  return( Name );
}
