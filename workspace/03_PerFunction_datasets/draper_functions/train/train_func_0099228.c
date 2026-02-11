line_error (defs, format, arg1, arg2)
     DEF_FILE *defs;
     char *format, *arg1, *arg2;
{
  if (defs->filename[0] != '/')
    fprintf (stderr, "%s", error_directory ? error_directory : "./");
  fprintf (stderr, "%s:%d:", defs->filename, defs->line_number + 1);
  fprintf (stderr, format, arg1, arg2);
  fprintf (stderr, "\n");
  fflush (stderr);
}
