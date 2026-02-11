taskSave ( task, taskdir )
Task *task;
char *taskdir;
{
  char *path;
  FILE *fp;
  int loop;

  path = (char *) malloc ( strlen ( taskdir ) + 10 );
  sprintf ( path, "%s/%d.task", taskdir, task->number );

  fp = fopen ( path, "w" );
  if ( !fp ) {
    free ( path );
    return ( TASK_ERROR_SYSTEM_ERROR );
  }

  fprintf ( fp, "Format: 1.2\n" );
  fprintf ( fp, "Name: %s\n", task->name );
  fprintf ( fp, "Created: %u\n", (unsigned int)task->created );
  fprintf ( fp, "Options: %u\n", task->options );
  fprintf ( fp, "Project: %d\n", task->project_id );
  fprintf ( fp, "Data:\n" );

  for ( loop = 0; loop < task->num_entries; loop++ ) {
    if ( task->entries[loop]->seconds )
      fprintf ( fp, "%04d%02d%02d %d\n",
        task->entries[loop]->year, task->entries[loop]->mon,
        task->entries[loop]->mday, task->entries[loop]->seconds );
  }

  fclose ( fp );
  free ( path );

  return ( 0 );
}
