taskAddAnnotation ( task, taskdir, text )
Task *task;
char *taskdir;
char *text;
{
  char *ptr, *path, *newtext;
  TaskAnnotation *a;
  FILE *fp;

  a = (TaskAnnotation *) malloc ( sizeof ( TaskAnnotation ) );
  memset ( a, '\0', sizeof ( TaskAnnotation ) );
  time ( &a->text_time );
  a->text = (char *) malloc ( strlen ( text ) + 1 );
  strcpy ( a->text, text );

  if ( task->annotations == NULL ) {
    task->annotations = (TaskAnnotation **) malloc (
      sizeof ( TaskAnnotation * ) );
  } else {
    task->annotations = (TaskAnnotation **) realloc ( task->annotations,
      ( task->num_annotations + 1 ) * sizeof ( TaskAnnotation * ) );
  }
  task->annotations[task->num_annotations] = a;
  task->num_annotations++;


  path = (char *) malloc ( strlen ( taskdir ) + 10 );
  sprintf ( path, "%s/%d.ann", taskdir, task->number );
  fp = fopen ( path, "a+" );
  if ( fp ) {
    newtext = (char *) malloc ( strlen ( text ) + 1 );
    strcpy ( newtext, text );
    for ( ptr = newtext; *ptr != '\0'; ptr++ )
      if ( *ptr == '\n' )
        *ptr = '\r';
    fprintf ( fp, "%d %s\n", (int)a->text_time, newtext );
    free ( newtext );
    fclose ( fp );
  }
  free ( path );
}
