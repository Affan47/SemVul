VasyDriveVexFile( String, Length )

  char *String;
  int   Length;
{
  VasyDriveLength += Length;

  if ( ( ! VasyDriveVexAtomLock                   ) &&
       ( VasyDriveLength >= VASY_DRIVE_VEX_LENGTH ) )
  {
    fprintf( VasyFile, "\n" );
    VasyDriveLength = 0;
  }

  if ( *String )
  {
    fwrite( String, sizeof(char), Length, VasyFile );
  }
}
