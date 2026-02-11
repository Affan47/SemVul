_arg_to_int(int    arg_id,
            int    argc,
            char  *argv[])
{
  char  *start = NULL;
  char  *end = NULL;
  long  retval = 0;

  if (arg_id < argc) {
    start = argv[arg_id];
    end = start + strlen(start);
    retval = strtol(start, &end, 0);
    if (end != start + strlen(start))
      _usage(argv[0], EXIT_FAILURE);
  }
  else
    _usage(argv[0], EXIT_FAILURE);

  return retval;
}
