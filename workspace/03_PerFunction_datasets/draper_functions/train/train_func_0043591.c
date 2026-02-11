projectLoad ( path, project )
char *path;
Project **project;
{
  FILE *fp;
  int fd;
  Project *newproject;
  char line[512], *ptr, *ptr2, temp[10], *annfile, *anntext;
  int len, created, number, options;
  struct stat buf;

  fp = fopen ( path, "r" );
  if ( !fp )
    return ( PROJECT_ERROR_SYSTEM_ERROR );

  for ( ptr = path + strlen ( path ) - 1; *ptr != '/' && ptr != path; ptr-- );
  if ( *ptr == '/' )
    ptr++;
  sscanf ( ptr, "%d.project", &number );

  fgets ( line, 512, fp );
  len = strlen ( line );
  if ( line[len-1] == '\n' )
    line[len-1] = '\0';
  if ( strcmp ( line, "Format: 1.0" ) && strcmp ( line, "Format: 1.1" ) &&
    strcmp ( line, "Format: 1.2" ) ) {
    fclose ( fp );
    return ( PROJECT_ERROR_BAD_FILE );
  }

  newproject = (Project *) malloc ( sizeof ( Project ) );
  memset ( newproject, '\0', sizeof ( Project ) );
  newproject->number = number;

  while ( fgets ( line, 512, fp ) ) {
    len = strlen ( line );
    if ( line[len-1] == '\n' )
      line[len-1] = '\0';
    if ( strncmp ( line, "Name:", 5 ) == 0 ) {
      ptr = line + 5;
      if ( *ptr == ' ' )
        ptr++;
      newproject->name = (char *) malloc ( strlen ( ptr ) + 1 );
      strcpy ( newproject->name, ptr );
    } else if ( strncmp ( line, "Created:", 8 ) == 0 ) {
      sscanf ( line + 8, "%d", &created );
      newproject->created = (time_t) created;
    } else if ( strncmp ( line, "Options:", 8 ) == 0 ) {
      sscanf ( line + 8, "%d", &options );
      newproject->options = (unsigned int) options;
    } else {
      fclose ( fp );
      projectFree ( newproject );
      return ( PROJECT_ERROR_BAD_FILE );
    }
  }
  fclose ( fp );

  projectAdd ( newproject );

  *project = newproject;

  return ( 0 );
}
