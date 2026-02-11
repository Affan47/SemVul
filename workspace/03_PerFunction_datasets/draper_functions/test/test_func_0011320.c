fork_execute (char **argv)
{
  struct pex_obj *pex;
  char *new_argv[3];
  char *at_args;
  FILE *args;
  int status;

  args_name = make_temp_file (".args");
  at_args = concat ("@", args_name, NULL);
  args = fopen (args_name, "w");
  if (args == NULL)
    fatal ("failed to open %s", args_name);

  status = writeargv (&argv[1], args);

  if (status)
    fatal ("could not write to temporary file %s",  args_name);

  fclose (args);

  new_argv[0] = argv[0];
  new_argv[1] = at_args;
  new_argv[2] = NULL;

  pex = collect_execute (new_argv);
  collect_wait (new_argv[0], pex);

  maybe_unlink_file (args_name);
  args_name = NULL;
  free (at_args);
}
