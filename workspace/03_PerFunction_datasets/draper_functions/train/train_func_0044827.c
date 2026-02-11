GetNextLine( char buf[], char line[] )
{
  char bufaux[BUF_SIZE]="";
  int i=0;
  int found=0;

  for ( i=0; i<strlen( buf ); ++i ) {
    line[i] = buf[i];
    line[i+1] = '\0';
    if ( line[i] == '\n' ) {
      found = 1;
      strcpy( bufaux, buf );
      strcpy( buf, zerochar );
      if ( strlen( &(bufaux[i+1]) ) > 0 ) {
        strcpy( buf, &(bufaux[i+1]) );
      }
      break;
    }
  }
  return found;
}
