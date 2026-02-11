KissGetValue()
{
  char *Scan;
  int   Value;

  Value = 0;

  for ( Scan = KissScanBuffer; *Scan != '\0'; Scan++ )
  {
    if ( isspace( *Scan ) ) break;
  }

  if ( Scan != KissScanBuffer )
  {
    *Scan = '\0';
    Value = atoi( KissScanBuffer );
    *Scan = ' ';

    KissScanBuffer = Scan;
  }

  if ( Value <= 0 )
  {
    fkserror( KISS_ERROR_VALUE, KissLineNumber );
  }

  return( Value );
}
