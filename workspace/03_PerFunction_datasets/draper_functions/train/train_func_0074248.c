projectSave ( project, projectdir )
Project *project;
char *projectdir;
{
  char *path;
  FILE *fp;
  int loop;

  path = (char *) malloc ( strlen ( projectdir ) + 20 );
  sprintf ( path, "%s/%d.project", projectdir, project->number );

  fp = fopen ( path, "w" );
  if ( !fp ) {
    free ( path );
    return ( PROJECT_ERROR_SYSTEM_ERROR );
  }

  fprintf ( fp, "Format: 1.2\n" );
  fprintf ( fp, "Name: %s\n", project->name );
  fprintf ( fp, "Created: %u\n", (unsigned int)project->created );
  fprintf ( fp, "Options: %u\n", project->options );

  fclose ( fp );
  free ( path );

  return ( 0 );
}
